// https://www.acmicpc.net/problem/1927
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

/*
 * 문제 아이디어
 *
 * 1. 힙 사용
 * 2. 입력별 분기 설정
 *
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    priority_queue<int, vector<int>, greater<int>> pq;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        if (x == 0)
        {
            if (!pq.empty())
            {
                cout << pq.top() << endl;
                pq.pop();
            }
            else
            {
                cout << 0 << endl;
            }
        }
        else
        {
            pq.push(x);
        }
    }

    return 0;
}
