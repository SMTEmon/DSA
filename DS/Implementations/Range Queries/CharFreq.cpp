#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.length();

    vector<vector<int>> pref(26, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++)
    {
        for (int c = 0; c < 26; c++)
        {
            pref[c][i + 1] = pref[c][i];
        }
        pref[s[i] - 'a'][i + 1]++;
    }

    int q;
    cin >> q;
    while (q--)
    {
        int L, R;
        cin >> L >> R;

        int maxFreq = -1;
        char bestChar = ' ';

        for (int c = 0; c < 26; c++)
        {
            int count = pref[c][R + 1] - pref[c][L];
            if (count > maxFreq)
            {
                maxFreq = count;
                bestChar = (char)('a' + c);
            }
        }
        cout << bestChar << endl;
    }

    return 0;
}