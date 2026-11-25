// https://www.acmicpc.net/problem/1966
#include <bits/stdc++.h>
#define endl "\n"
#define INF 1e18
#define dir4 {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
#define dir8 {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}
#define board_condition(row, col, n, m) (row >= 0 && row < n && col >= 0 && col < m)
#define FASTIO cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define F first
#define S second
#define PB push_back
#define REP(i, a, b) for (int i = a; i < b; i++)
#define SORT(x) sort(x.begin(), x.end())
#define REV(x) reverse(x.begin(), x.end())
#define UNIQUE(x) x.erase(unique(x.begin(), x.end()), x.end())
#define VINPUT(v, n) \
    REP(i, 0, n)     \
    {                \
        int tmp;     \
        cin >> tmp;  \
        v.PB(tmp);   \
    }
#define VOUTPUT(v)                               \
    REP(i, 0, v.size()) { cout << v[i] << " "; } \
    cout << endl
#define V2DINPUT(v, n, m) \
    REP(i, 0, n)          \
    {                     \
        vi tmpv;          \
        REP(j, 0, m)      \
        {                 \
            int tmp;      \
            cin >> tmp;   \
            tmpv.PB(tmp); \
        }                 \
        v.PB(tmpv);       \
    }
#define V2DOUTPUT(v)                                       \
    REP(i, 0, v.size())                                    \
    {                                                      \
        REP(j, 0, v[i].size()) { cout << v[i][j] << " "; } \
        cout << endl;                                      \
    }                                                      \
    cout << endl
#define WATCH(x) cout << #x << " : " << x << endl
#define DEBUG(x) cout << "DB - " << x << endl
#define PRINT(x) cout << x << endl
#define NVOUTPUT(x)
#define NV2DOUTPUT(x)
#define NWATCH(x)
#define NDEBUG(x)
#define NPRINT(x)

using namespace std;

/*
 * 문제 아이디어
 * 1. 큐 구현 문제
 *
 */

int main()
{
    FASTIO;
    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m;
        cin >> n >> m;
        queue<pair<int, int>> q;
        priority_queue<int> pq;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            q.push({i, tmp});
            pq.push(tmp);
        }
        int cnt = 1;
        while (true)
        {
            if (q.front().S == pq.top())
            {
                if (q.front().F == m)
                {
                    cout << cnt << endl;
                    break;
                }
                else
                {
                    pq.pop();
                    q.pop();
                    cnt++;
                }
            }
            else
            {
                q.push(q.front());
                q.pop();
            }
        }
    }

    return 0;
}
