#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void DP(vector<lli> price, vector<lli> pages, vector<vector<lli>> &dp, lli n, lli x)
{
    lli p_size = pages.size();

    for (lli i = 1; i <= p_size; i++)
    {
        for (lli j = 1; j <= x; j++)
        {
            if (price[i - 1] > j)
            {
                dp[i][j] = dp[i - 1][j]; // skip
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j],
                               dp[i - 1][j - price[i - 1]] + pages[i - 1]);
            }
        }
    }
}

int main()
{
    lli n, x;

    cin >> n >> x;

    vector<lli> price(n, 0);
    vector<lli> pages(n, 0);

    for (lli i = 0; i < n; i++)
    {
        cin >> price[i];
    }

    for (lli i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    vector<vector<lli>> dp(n + 1, vector<lli>(x + 1, 0));

    DP(price, pages, dp, n, x);

    cout << dp[pages.size()][x];
}