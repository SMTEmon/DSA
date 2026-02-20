#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    // input
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // prefix sum
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        pref[i + 1] = pref[i] + a[i];
    }

    int q;
    cin >> q;
    while (q--)
    {
        int L, R;
        cin >> L >> R;
        cout << pref[R + 1] - pref[L] << endl;
    }

    return 0;
}