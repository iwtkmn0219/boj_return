// https://www.acmicpc.net/problem/9012
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

/*
 * 문제 아이디어
 * 1. 스택같은 숫자 사용한다.
 * 2. 0임에도 보임에도 불구하고 ')'가 나오면 NO
 * 3. 끝났을때 0이 아니면 NO
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        int cnt = 0;
        string s;
        cin >> s;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                cnt++;
            }
            else
            {
                cnt--;
                if (cnt == -1)
                {
                    break;
                }
            }
        }
        if (cnt == 0)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}
