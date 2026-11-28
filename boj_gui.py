"""백준 풀이 도우미 (GUI 버전).

- 문제 번호를 입력하고 Enter (또는 [생성/실행] 버튼)
  - src/<번호>.cpp 가 없으면 템플릿으로 생성하고 VS Code 로 엽니다.
  - 있으면 컴파일(소스가 바뀌었을 때만) 후, 왼쪽 입력칸의 내용을 입력으로 넣어 실행합니다.
- 입력칸에서 Ctrl+Enter 로도 실행할 수 있습니다.
- 제한 시간을 넘기면 프로그램을 강제로 종료합니다.
"""

import queue
import shutil
import subprocess
import threading
import time
import tkinter as tk
from pathlib import Path
from tkinter import ttk
from tkinter.scrolledtext import ScrolledText

from boj import BUILD_DIR, CXX, CXXFLAGS, DEFAULT_TEMPLATE, ROOT, SRC_DIR, TEMPLATE

# 콘솔 창이 깜빡이지 않도록 (Windows)
NO_WINDOW = getattr(subprocess, "CREATE_NO_WINDOW", 0)
FONT = ("Consolas", 11)


def decode(data: bytes) -> str:
    for enc in ("utf-8", "cp949"):
        try:
            text = data.decode(enc)
            break
        except UnicodeDecodeError:
            pass
    else:
        text = data.decode("utf-8", errors="replace")
    return text.replace("\r\n", "\n")


def open_in_editor(path: Path) -> bool:
    code = shutil.which("code")
    if not code:
        return False
    subprocess.Popen([code, str(path)], creationflags=NO_WINDOW)
    return True


class App:
    def __init__(self, root: tk.Tk) -> None:
        self.root = root
        self.busy = False
        self.queue: queue.Queue = queue.Queue()
        root.after(50, self.poll_queue)
        root.title("백준 풀이 도우미")
        root.geometry("900x560")
        root.minsize(600, 360)

        # ── 상단: 문제 번호 / 버튼 / 제한 시간 ──
        top = ttk.Frame(root, padding=(10, 10, 10, 4))
        top.pack(fill="x")

        ttk.Label(top, text="문제 번호").pack(side="left")
        self.num_var = tk.StringVar()
        self.num_entry = ttk.Entry(top, textvariable=self.num_var, width=10, font=FONT)
        self.num_entry.pack(side="left", padx=(6, 6))
        self.num_entry.bind("<Return>", lambda e: self.on_go())
        self.num_entry.focus_set()

        self.go_btn = ttk.Button(top, text="생성/실행", command=self.on_go)
        self.go_btn.pack(side="left")
        ttk.Button(top, text="VS Code로 열기", command=self.on_open).pack(side="left", padx=(6, 0))

        self.timeout_var = tk.StringVar(value="5")
        ttk.Label(top, text="초").pack(side="right")
        ttk.Spinbox(top, from_=1, to=60, width=4, textvariable=self.timeout_var).pack(side="right", padx=4)
        ttk.Label(top, text="제한 시간").pack(side="right")

        # ── 가운데: 입력 / 출력 ──
        panes = ttk.PanedWindow(root, orient="horizontal")
        panes.pack(fill="both", expand=True, padx=10, pady=4)

        in_frame = ttk.Frame(panes)
        ttk.Label(in_frame, text="입력  (Ctrl+Enter: 실행)").pack(anchor="w")
        self.input_text = ScrolledText(in_frame, font=FONT, undo=True, wrap="none")
        self.input_text.pack(fill="both", expand=True)
        self.input_text.bind("<Control-Return>", self.on_ctrl_enter)
        panes.add(in_frame, weight=1)

        out_frame = ttk.Frame(panes)
        ttk.Label(out_frame, text="출력").pack(anchor="w")
        self.output_text = ScrolledText(out_frame, font=FONT, wrap="none", state="disabled")
        self.output_text.tag_configure("error", foreground="#c62828")
        self.output_text.tag_configure("info", foreground="#666666")
        self.output_text.pack(fill="both", expand=True)
        panes.add(out_frame, weight=1)

        # ── 하단: 상태 표시줄 ──
        self.status_var = tk.StringVar(value="문제 번호를 입력하세요.")
        self.status = ttk.Label(root, textvariable=self.status_var, padding=(10, 4, 10, 8))
        self.status.pack(fill="x")

    # ── 화면 갱신 도우미 ──
    def set_output(self, text: str, tag: str | None = None) -> None:
        self.output_text.configure(state="normal")
        self.output_text.delete("1.0", "end")
        if text:
            self.output_text.insert("1.0", text, tag or ())
        self.output_text.configure(state="disabled")

    def set_status(self, text: str) -> None:
        self.status_var.set(text)

    def set_busy(self, busy: bool) -> None:
        self.busy = busy
        self.go_btn.configure(state="disabled" if busy else "normal")

    def ui(self, func, *args) -> None:
        """작업 스레드에서 화면을 바꿀 때 사용 (메인 스레드가 큐에서 꺼내 실행)."""
        self.queue.put((func, args))

    def poll_queue(self) -> None:
        while True:
            try:
                func, args = self.queue.get_nowait()
            except queue.Empty:
                break
            func(*args)
        self.root.after(50, self.poll_queue)

    # ── 이벤트 ──
    def get_num(self) -> str | None:
        num = self.num_var.get().strip()
        if not num.isdigit():
            self.set_status("문제 번호는 숫자여야 합니다.")
            self.num_entry.focus_set()
            return None
        return num

    def on_ctrl_enter(self, event) -> str:
        self.on_go()
        return "break"  # 입력칸에 줄바꿈이 들어가지 않게

    def on_open(self) -> None:
        num = self.get_num()
        if num is None:
            return
        src = SRC_DIR / f"{num}.cpp"
        if not src.exists():
            self.set_status(f"src/{num}.cpp 파일이 없습니다. [생성/실행]으로 먼저 만드세요.")
        elif not open_in_editor(src):
            self.set_status("VS Code(code 명령)를 찾을 수 없습니다.")

    def on_go(self) -> None:
        if self.busy:
            return
        num = self.get_num()
        if num is None:
            return
        src = SRC_DIR / f"{num}.cpp"
        if not src.exists():
            self.create(num, src)
            return

        try:
            timeout = max(1.0, float(self.timeout_var.get()))
        except ValueError:
            timeout = 5.0
        stdin = self.input_text.get("1.0", "end-1c")
        if stdin and not stdin.endswith("\n"):
            stdin += "\n"

        self.set_busy(True)
        self.set_output("")
        threading.Thread(target=self.build_and_run, args=(num, src, stdin, timeout), daemon=True).start()

    # ── 실제 작업 ──
    def create(self, num: str, src: Path) -> None:
        SRC_DIR.mkdir(exist_ok=True)
        template = TEMPLATE.read_text(encoding="utf-8") if TEMPLATE.exists() else DEFAULT_TEMPLATE
        src.write_text(template.replace("{num}", num), encoding="utf-8")
        opened = open_in_editor(src)
        self.set_output(f"src/{num}.cpp 를 생성했습니다.\nhttps://www.acmicpc.net/problem/{num}\n", "info")
        self.set_status(f"[생성] src/{num}.cpp" + ("  (VS Code에서 열었습니다)" if opened else ""))

    def build_and_run(self, num: str, src: Path, stdin: str, timeout: float) -> None:
        try:
            exe = BUILD_DIR / f"{num}.exe"
            if not (exe.exists() and exe.stat().st_mtime >= src.stat().st_mtime):
                self.ui(self.set_status, f"[컴파일 중] {src.name} ...")
                BUILD_DIR.mkdir(exist_ok=True)
                try:
                    result = subprocess.run(
                        [CXX, *CXXFLAGS, "-o", str(exe), str(src)],
                        capture_output=True, creationflags=NO_WINDOW,
                    )
                except FileNotFoundError:
                    self.ui(self.set_output, f"컴파일러를 찾을 수 없습니다: {CXX}", "error")
                    self.ui(self.set_status, "[컴파일 실패]")
                    return
                if result.returncode != 0:
                    msg = decode(result.stderr).replace(str(SRC_DIR) + "\\", "")
                    self.ui(self.set_output, msg, "error")
                    self.ui(self.set_status, "[컴파일 실패]")
                    return

            self.ui(self.set_status, "[실행 중] ...")
            start = time.perf_counter()
            proc = subprocess.Popen(
                [str(exe)], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE, creationflags=NO_WINDOW,
            )
            try:
                out, err = proc.communicate(stdin.encode("utf-8"), timeout=timeout)
            except subprocess.TimeoutExpired:
                proc.kill()
                out, err = proc.communicate()
                text = decode(out)
                self.ui(self.set_output, text + ("\n" if text and not text.endswith("\n") else "")
                        + f"[시간 초과] {timeout:g}초 안에 끝나지 않아 강제 종료했습니다.", "error")
                self.ui(self.set_status, f"[시간 초과] {timeout:g}초")
                return
            elapsed = (time.perf_counter() - start) * 1000

            text = decode(out)
            if err:
                text += ("\n" if text and not text.endswith("\n") else "") + "[stderr]\n" + decode(err)
            ok = proc.returncode == 0
            self.ui(self.set_output, text, None if ok else "error")
            status = "정상 종료" if ok else f"런타임 에러 (종료 코드 {proc.returncode})"
            self.ui(self.set_status, f"[{status}] {elapsed:.0f} ms")
        except Exception as e:  # 예상 못 한 오류도 화면에 표시
            self.ui(self.set_output, f"{type(e).__name__}: {e}", "error")
            self.ui(self.set_status, "[오류]")
        finally:
            self.ui(self.set_busy, False)


def main() -> None:
    try:  # 고해상도 화면에서 글자가 흐려지지 않게
        from ctypes import windll
        windll.shcore.SetProcessDpiAwareness(1)
    except Exception:
        pass
    root = tk.Tk()
    App(root)
    root.mainloop()


if __name__ == "__main__":
    main()
