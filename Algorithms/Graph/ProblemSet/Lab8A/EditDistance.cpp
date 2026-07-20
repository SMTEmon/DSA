#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void DP(vector<vector<lli>> &dp, string &n, string &m)
{
    lli size_n = n.size(), size_m = m.size();
    for (lli i = 1; i < size_n; i++)
    {
        for (lli j = 1; j < size_m; j++)
        {
            if (n[i] == m[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
}

int main()
{
    string n, m;
    cin >> n >> m;

    lli i = n.size(), j = m.size();

    n = " " + n;
    m = " " + m;

    vector<vector<lli>> dp(i + 1, vector<lli>(j + 1, 0));

    DP(dp, n, m);

    cout << max(i, j) - dp[i][j] << endl;
}