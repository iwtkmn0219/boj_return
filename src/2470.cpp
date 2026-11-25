// https://www.acmicpc.net/problem/2470
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
 * 1. 이분 탐색 사용하기
 * 1.2. 정렬 후 모든 값에 대한 최적 조합 탐색
 *
 */

int n;
vi v;

int find_my_girlfriend(int x)
{
    int s = x + 1, e = v.size() - 1;
    while (s + 1 < e)
    {
        int m = (s + e) / 2;
        if (v[x] + v[m] < 0)
            s = m;
        else
            e = m;
    }
    if (abs(v[s] + v[x]) < abs(v[e] + v[x]))
        return s;
    else
        return e;
}

int main()
{
    FASTIO;
    cin >> n;
    VINPUT(v, n);
    SORT(v);
    pi result = {v.front(), v.back()};
    for (int i = 0; i < n - 1; i++)
    {
        int gf = find_my_girlfriend(i);
        if (abs(v[i] + v[gf]) < abs(result.S + result.F))
            result = {min(v[i], v[gf]), max(v[i], v[gf])};
    }

    cout << result.F << " " << result.S;

    return 0;
}
