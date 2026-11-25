// https://www.acmicpc.net/problem/1874
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
 * 1. 일반적인 구현문제라고 생각함.
 * 2. 다만, 스택에서 제거하고 싶은 수가 스택에 존재하지만 뺄 수 없는 상태라면
 *      2.1 그대로 불가능 판정
 *      2.2 끝까지 진행되면 가능 판정
 * 3. push, pop 로그를 따로 저장하고, 가능 판정이 나왔을 때 출력
 *
 */

int main()
{
    FASTIO;
    vs stack_log;
    stack<int> s2;
    queue<int> q;
    int n, tmp;
    cin >> n;
    vi visited(100000, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        q.push(tmp);
    }
    int num = 1;
    while (!q.empty())
    {
        if (num <= n) // 넣기
        {
            // WATCH(num);
            visited[num] = 1;
            s2.push(num++);
            stack_log.push_back("+");
        }

        // 비교
        while (!s2.empty() && !q.empty() && s2.top() == q.front())
        {
            // WATCH(q.front());
            q.pop();
            s2.pop();
            stack_log.push_back("-");
        }

        if (!q.empty() && visited[q.front()])
        {
            // DEBUG("NO");
            // WATCH(s2.top());
            // WATCH(q.front());
            break;
        }
    }
    if (q.empty())
    {
        VOUTPUTENDL(stack_log);
    }
    else
    {
        cout << "NO";
    }

    return 0;
}
