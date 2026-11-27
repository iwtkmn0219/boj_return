// https://www.acmicpc.net/problem/1002
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
 *
 * 1. 문제 잘못 이해했음(교차점이 정수가 아님)
 * 2. 원 내접, 외접 문제로 재해석
 *
 */

int tc;
int x1_center, y1_center, r1, x2_center, y2_center, r2;

bool is_in_circle(int x, int y)
{
    if ((x - x1_center) * (x - x1_center) + (y - y1_center) * (y - y1_center) == r1 * r1)
        if ((x - x2_center) * (x - x2_center) + (y - y2_center) * (y - y2_center) == r2 * r2)
            return true;
    return false;
}

int main()
{
    FASTIO;

    cin >> tc;
    while (tc--)
    {
        cin >> x1_center >> y1_center >> r1 >> x2_center >> y2_center >> r2;

        int rp_pow = (r1 + r2) * (r1 + r2);
        int rm_pow = (r1 - r2) * (r1 - r2);
        int distance_2 = (x2_center - x1_center) * (x2_center - x1_center) + (y2_center - y1_center) * (y2_center - y1_center);

        // 두 원이 동일할 때
        if (x1_center == x2_center && y1_center == y2_center && r1 == r2)
        {
            cout << -1 << endl;
            continue;
        }

        // WATCH(distance_2);
        // WATCH(rp_pow);
        // WATCH(rm_pow);
        // 두 원이 한 점에서 만날 때
        if (rp_pow == distance_2 || rm_pow == distance_2)
        {
            cout << 1 << endl;
        }
        // 그냥 못 만날 때
        else if (rp_pow < distance_2 || rm_pow > distance_2)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }

    return 0;
}
