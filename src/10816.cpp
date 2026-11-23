// https://www.acmicpc.net/problem/10816
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

/*
 * 문제 아이디어
 *
 * 1. map에 등록 후 빼내기
 *
 */

unordered_map<int, int> umap;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (umap.count(tmp))
        {
            umap[tmp]++;
        }
        else
        {
            umap[tmp] = 1;
        }
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        cout << umap[tmp] << " ";
    }

    return 0;
}
