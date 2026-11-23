// https://www.acmicpc.net/problem/1316
#include <bits/stdc++.h>

using namespace std;

/*
 * 문제 아이디어
 * 1. 알파벳 전체에 해당하는 배열을 만든다.
 * 2. 각 TC마다 순차 탐색을 하며, 현재 소속되어있는 character 윈도우에 한해 배열 존재 여부를 검사한다.
 * 3. 만약, 이미 기록되어있는 상태라면 더이상 '그룹 단어'가 아니다.
 * 4. 기록되어있지 않다면 배열에 체크한 뒤 넘어간다.
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        char prev = tmp[0];
        vector<int> v;
        v.resize(26, 0);
        v[prev - 'a'] = 1;
        bool flag = true;
        for (int j = 1; j < tmp.length(); j++)
        {
            if (prev == tmp[j])
            {
                continue;
            }
            else
            {
                if (v[tmp[j] - 'a'] == 1)
                {
                    flag = false;
                    break;
                }
                else
                {
                    v[tmp[j] - 'a'] = 1;
                    prev = tmp[j];
                }
            }
        }
        if (flag)
            result++;
    }
    cout << result;
    return 0;
}
