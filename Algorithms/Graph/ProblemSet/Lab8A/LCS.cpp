#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void DP(vector<vector<lli>> &dp, vector<lli> &arr1, vector<lli> &arr2, lli n, lli m)
{
    for (lli i = 1; i <= n; i++)
    {
        for (lli j = 1; j <= m; j++)
        {
            if (arr1[i] == arr2[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
}

void DPreconstruction(vector<vector<lli>> dp, vector<lli> arr1, vector<lli> arr2, lli n, lli m)
{
    lli i = n, j = m;

    vector<lli> out;

    while (i > 0 && j > 0)
    {
        if (arr1[i] == arr2[j])
        {
            out.push_back(arr1[i]);
            i--;
            j--;
        }
        else
        {
            if (dp[i][j - 1] <= dp[i - 1][j])
            {
                i--;
            }
            else
                j--;
        }
    }

    lli size_out = out.size();

    for (lli k = size_out - 1; k >= 0; k--)
    {
        cout << out[k] << " ";
    }
}

int main()
{
    lli n, m;
    cin >> n >> m;

    vector<lli> arr1(n + 1);
    vector<lli> arr2(m + 1);

    for (lli i = 1; i <= n; i++)
    {
        cin >> arr1[i];
    }

    for (lli i = 1; i <= m; i++)
    {
        cin >> arr2[i];
    }

    vector<vector<lli>> dp(n + 1, vector<lli>(m + 1, 0));

    DP(dp, arr1, arr2, n, m);

    cout << dp[n][m] << endl;

    DPreconstruction(dp, arr1, arr2, n, m);
}