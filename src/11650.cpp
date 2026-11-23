// https://www.acmicpc.net/problem/11650
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

/*
 * 문제 아이디어
 *
 * 1. 정렬함수를 새로 만들어서 사용한다.
 *
 */

bool compare(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    vector<pair<int, int>> v;
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }

    return 0;
}
