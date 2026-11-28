// https://www.acmicpc.net/problem/1654
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
 * 1. 알고리즘은 이분 탐색이라고 생각함.
 * 2. 적합한 랜선 길이를 이분 탐색을 통해 찾는 것이 메인 아이디어
 * 3. 이미 가지고 있는 k개의 랜선 중 가장 작은 랜선을
 *      잘라서 만들 수 있는 가장 큰 랜선으로 두고 이분 탐색을 진행한다.
 *
 */

long long k, n, tmp, start_len = 0, end_len = 0;
vi lan_cables;

int count_lan(long long x)
{
    int cnt = 0;
    for (const auto &e : lan_cables)
        cnt += (e / x);
    return cnt;
}

long long get_opt_len()
{
    while (start_len + 1 < end_len)
    {
        long long mid_len = ((long long)start_len + (long long)end_len) / 2;
        // WATCH(start_len);
        // WATCH(end_len);
        // WATCH(count_lan(mid_len));
        if (count_lan(mid_len) < n)
            end_len = mid_len;
        else
            start_len = mid_len;
    }

    if (count_lan(end_len) >= n)
        return end_len;
    else
        return start_len;
}

int main()
{
    FASTIO;

    cin >> k >> n;
    for (int i = 0; i < k; i++)
    {
        cin >> tmp;
        end_len = max(tmp, end_len);
        lan_cables.PB(tmp);
    }
    cout << get_opt_len();

    return 0;
}
