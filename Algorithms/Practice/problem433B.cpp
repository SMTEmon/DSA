// https://codeforces.com/problemset/problem/433/B

//
// Created by SMTEmon.
//

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void DP(vector<lli> &dpPreSum, vector<lli> &inn, lli n)
{
    for (lli i = 1; i <= n; i++)
    {
        dpPreSum[i] = dpPreSum[i - 1] + inn[i - 1];
    }
}

void DP2(vector<lli> &dp2, vector<lli> &inn, lli n)
{
    sort(inn.begin(), inn.end());
    for (lli i = 1; i <= n; i++)
    {
        dp2[i] = dp2[i - 1] + inn[i - 1];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    lli n;
    cin >> n;

    vector<lli> inn(n);

    for (lli i = 0; i < n; i++)
    {
        cin >> inn[i];
    }

    lli m;
    cin >> m;

    vector<lli> dpPreSum(n + 1, 0);
    vector<lli> dp2(n + 1, 0);

    DP(dpPreSum, inn, n);
    DP2(dp2, inn, n);

    while (m--)
    {
        lli type, l, r;
        cin >> type >> l >> r;

        if (type == 1)
        {
            // lli res = 0;
            // for (lli i = l; i <= r; i++)
            // {
            //     res += dpPreSum[i];
            // }
            cout << dpPreSum[r] - dpPreSum[l - 1] << endl;
        }

        if (type == 2)
        {
            // lli res = 0;
            // for (lli i = l - 1; i < r; i++)
            // {
            //     res += inn[i];
            // }
            cout << dp2[r] - dp2[l - 1] << endl;
        }
    }

    return 0;
}