// https://www.acmicpc.net/problem/11659
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

/*
 * 문제 아이디어
 *
 * 1. 누적합 사용
 *
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> v, prefix_sum;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    prefix_sum.push_back(0);
    prefix_sum.push_back(v[0]);
    for (int i = 1; i < n; i++)
    {
        prefix_sum.push_back(prefix_sum.back() + v[i]);
    }
    for (int tc = 0; tc < m; tc++)
    {
        int a, b;
        cin >> a >> b;
        cout << prefix_sum[b] - prefix_sum[a - 1] << endl;
    }
    return 0;
}
