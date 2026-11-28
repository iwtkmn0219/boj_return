// https://www.acmicpc.net/problem/2667
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
 * 1. 모든 점에 대해 BFS를 실행한다.
 * 1.1. 만약 이전에 방문했던 집이라면 패스한다.
 * 1.2. 처음 방문하는 집이라면 집의 개수를 센다.
 * 2. BFS를 통해 현재 속한 집의 크기를 세고 따로 저장해둔다.
 *
 */

int n, result = 0, dir[4][2] = dir4;
vi home_sizes;
vvi board, visited;

int bfs(int r, int c)
{
    int home_size = 1;
    queue<pi> q;
    q.push({r, c});
    visited[r][c] = 1;
    while (!q.empty())
    {
        int cr = q.front().F;
        int cc = q.front().S;
        q.pop();
        for (const auto &d : dir)
        {
            int nr = cr + d[0];
            int nc = cc + d[1];
            if (board_condition(nr, nc, n, n))
            {
                if (board[nr][nc] && !visited[nr][nc])
                {
                    visited[nr][nc] = 1;
                    q.push({nr, nc});
                    home_size++;
                }
            }
        }
    }

    return home_size;
}

int main()
{
    FASTIO;

    cin >> n;
    board.resize(n, vi(n, 0));
    visited.resize(n, vi(n, 0));
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < n; j++)
        {
            board[i][j] = tmp[j] - '0';
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] && !visited[i][j])
            {
                result++;
                home_sizes.PB(bfs(i, j));
            }
        }
    }

    SORT(home_sizes);

    cout << result << endl;
    VOUTPUTENDL(home_sizes);

    return 0;
}
