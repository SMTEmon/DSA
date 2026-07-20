#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void DP(vector<lli> &DP, vector<lli> coins, lli n, lli x)
{
    DP[0] = 1;

    for (lli coin : coins)
    {
        for (lli i = coin; i <= x; i++)
        {
            DP[i] += DP[i - coin];
        }
    }
}

int main()
{
    lli n, x;
    cin >> n >> x;

    vector<lli> coins;

    for (int i = 0; i < n; i++)
    {
        lli temp;
        cin >> temp;
        coins.push_back(temp);
    }

    sort(coins.begin(), coins.end());

    vector<lli> DP1(x + 1, 0);

    DP(DP1, coins, n, x);

    cout << DP1[x] << endl;
}