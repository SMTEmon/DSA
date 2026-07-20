#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void DP(vector<lli> coins, vector<lli> count, vector<lli> &dp, lli n, lli x)
{
    dp[0] = 0;

    for (lli sum = 1; sum <= x; sum++)
    {
        lli min_ic = -1;
        for (lli ic = 0; ic < n; ic++)
        {
            if (count[ic] <= 0)
                continue;
            if (sum >= coins[ic])
            {
                if (dp[sum] > dp[sum - coins[ic]] + 1)
                {
                    dp[sum] = dp[sum - coins[ic]] + 1;
                    min_ic = ic;
                }
            }
        }
        if (min_ic != -1)
            count[min_ic]--;
    }
}

int main()
{
    lli n, x;
    cin >> n >> x;

    vector<lli> coins(n);
    vector<lli> count(n);

    for (lli i = 0; i < n; i++)
    {
        cin >> coins[i];
        cin >> count[i];
    }

    vector<lli> dp(x + 1, INT_MAX);

    DP(coins, count, dp, n, x);
    if (dp[x] != INT_MAX)
        cout << dp[x] << endl;
    else
        cout << -1;
}