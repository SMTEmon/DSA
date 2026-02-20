#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        stack<char> s;
        string str;
        getline(cin, str);

        bool flag = false;

        for (int j = 0; j < str.size(); j++)
        {
            if (str[j] == '(' or str[j] == '[')
                s.push(str[j]);
            else if (str[j] == ')')
            {
                if (s.empty() or s.top() != '(')
                {
                    flag = true;
                    break;
                }
                else
                    s.pop();
            }
            else if (str[j] == ']')
            {
                if (s.empty() or s.top() != '[')
                {
                    flag = true;
                    break;
                }
                else
                    s.pop();
            }
        }

        if (s.empty() && !flag)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}