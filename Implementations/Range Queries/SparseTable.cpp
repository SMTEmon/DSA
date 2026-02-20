#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100005;
const int K = 20;
int table[MAXN][K];
int a[MAXN];

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        table[i][0] = a[i];
    }

    for (int j = 1; j < K; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int L, R;
        cin >> L >> R;

        int len = R - L + 1;
        int j = log2(len);

        int answer = min(table[L][j], table[R - (1 << j) + 1][j]);
        cout << answer << endl;
    }

    return 0;
}