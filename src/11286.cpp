// https://www.acmicpc.net/problem/11286
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
#define VOUTPUTENDL(v)                            \
    REP(i, 0, v.size()) { cout << v[i] << endl; } \
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

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef pair<int, int> pi;
struct point
{
    int x, y;
};

/*
 * 문제 아이디어
 *
 * 1. 음수 힙과 양수 힙을 두개를 만든다.
 * 2. pop 요청 시 마다 두 힙 top의 절댓값을 비교하고 pop한다.
 *
 */

priority_queue<int, vi, greater<int>> plus_pq;
priority_queue<int> minus_pq;
int n, x;

int main()
{
    FASTIO;

    cin >> n;
    while (n--)
    {
        cin >> x;
        if (x == 0)
        {
            if (minus_pq.empty() && plus_pq.empty())
                cout << 0 << endl;
            else if (minus_pq.empty())
            {
                cout << plus_pq.top() << endl;
                plus_pq.pop();
            }
            else if (plus_pq.empty())
            {
                cout << minus_pq.top() << endl;
                minus_pq.pop();
            }
            else if (-minus_pq.top() == plus_pq.top())
            {
                cout << minus_pq.top() << endl;
                minus_pq.pop();
            }
            else
            {
                if (-minus_pq.top() < plus_pq.top())
                {
                    cout << minus_pq.top() << endl;
                    minus_pq.pop();
                }
                else
                {
                    cout << plus_pq.top() << endl;
                    plus_pq.pop();
                }
            }
        }
        else
        {
            if (x > 0)
                plus_pq.push(x);
            else
                minus_pq.push(x);
        }
    }

    return 0;
}
