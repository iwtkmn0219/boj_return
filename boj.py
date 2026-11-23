"""백준 풀이 도우미.

사용법:
    boj 1000        # 파일이 없으면 src/1000.cpp 생성, 있으면 컴파일 후 실행
    boj             # 문제 번호를 반복해서 입력받는 대화형 모드

- 새 문제를 만들면 src/<번호>.cpp 와 빈 input/<번호>.txt 가 함께 생깁니다.
- input/<번호>.txt 에 예제 입력을 붙여넣어 두면 실행할 때 그 파일이 입력으로 들어갑니다.
  파일이 비어 있으면 키보드로 직접 입력합니다 (끝낼 때 Ctrl+Z, Enter).
- 소스가 바뀌었을 때만 다시 컴파일합니다.
- 컴파일러는 환경변수 BOJ_CXX 로 바꿀 수 있습니다 (기본값: g++).
"""

import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent
SRC_DIR = ROOT / "src"
INPUT_DIR = ROOT / "input"
BUILD_DIR = ROOT / "build"
TEMPLATE = ROOT / "template.cpp"

CXX = os.environ.get("BOJ_CXX", "g++")
CXXFLAGS = ["-std=c++17", "-O2", "-Wall", "-DLOCAL"]

DEFAULT_TEMPLATE = """\
// https://www.acmicpc.net/problem/{num}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
"""


def create(num: str, src: Path, inp: Path) -> None:
    SRC_DIR.mkdir(exist_ok=True)
    INPUT_DIR.mkdir(exist_ok=True)
    template = TEMPLATE.read_text(encoding="utf-8") if TEMPLATE.exists() else DEFAULT_TEMPLATE
    src.write_text(template.replace("{num}", num), encoding="utf-8")
    if not inp.exists():
        inp.touch()
    print(f"[생성] {src.relative_to(ROOT)}")
    print(f"[생성] {inp.relative_to(ROOT)}  (예제 입력을 여기에 붙여넣으세요)")
    print(f"       https://www.acmicpc.net/problem/{num}")

    code = shutil.which("code")
    if code:
        subprocess.run([code, str(src)], shell=False)


def compile_(src: Path, exe: Path) -> bool:
    if exe.exists() and exe.stat().st_mtime >= src.stat().st_mtime:
        return True
    BUILD_DIR.mkdir(exist_ok=True)
    print(f"[컴파일] {CXX} {' '.join(CXXFLAGS)} {src.name}")
    result = subprocess.run([CXX, *CXXFLAGS, "-o", str(exe), str(src)])
    if result.returncode != 0:
        print("[컴파일 실패]")
        return False
    return True


def run(exe: Path, inp: Path) -> None:
    use_file = inp.exists() and inp.stat().st_size > 0
    if use_file:
        print(f"[실행] 입력: {inp.relative_to(ROOT)}")
        print("-" * 40)
        with inp.open("rb") as f:
            start = time.perf_counter()
            result = subprocess.run([str(exe)], stdin=f)
    else:
        print("[실행] 입력을 직접 입력하세요 (끝: Ctrl+Z 후 Enter)")
        print("-" * 40)
        start = time.perf_counter()
        result = subprocess.run([str(exe)])
    elapsed = (time.perf_counter() - start) * 1000
    print("-" * 40)
    status = "정상 종료" if result.returncode == 0 else f"종료 코드 {result.returncode}"
    print(f"[{status}] {elapsed:.0f} ms")


def solve(num: str) -> None:
    if not num.isdigit():
        print(f"문제 번호는 숫자여야 합니다: {num!r}")
        return
    src = SRC_DIR / f"{num}.cpp"
    inp = INPUT_DIR / f"{num}.txt"
    exe = BUILD_DIR / f"{num}.exe"

    if not src.exists():
        create(num, src, inp)
        return
    if compile_(src, exe):
        run(exe, inp)


def main() -> None:
    sys.stdout.reconfigure(line_buffering=True)
    if len(sys.argv) > 1:
        for num in sys.argv[1:]:
            solve(num.strip())
        return

    while True:
        try:
            num = input("\n문제 번호 (종료: q) > ").strip().lstrip("﻿")
        except (EOFError, KeyboardInterrupt):
            print()
            break
        if num.lower() in ("q", "quit", "exit"):
            break
        if num:
            solve(num)


if __name__ == "__main__":
    main()
