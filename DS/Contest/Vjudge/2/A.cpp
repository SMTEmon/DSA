//
// Created by SMTEmon.
//

#include <bits/stdc++.h>

using namespace std;

void solve(int caseNum)
{
    stack<string> backward;
    stack<string> forward;
    string currentUrl = "http://www.lightoj.com/";
    string command;

    cout << "Case " << caseNum << ":" << endl;

    while (cin >> command && command != "QUIT")
    {
        if (command == "VISIT")
        {
            string url;
            cin >> url;
            backward.push(currentUrl);
            currentUrl = url;
            while (!forward.empty())
            {
                forward.pop();
            }
            cout << currentUrl << endl;
        }
        else if (command == "BACK")
        {
            if (backward.empty())
            {
                cout << "Ignored" << endl;
            }
            else
            {
                forward.push(currentUrl);
                currentUrl = backward.top();
                backward.pop();
                cout << currentUrl << endl;
            }
        }
        else if (command == "FORWARD")
        {
            if (forward.empty())
            {
                cout << "Ignored" << endl;
            }
            else
            {
                backward.push(currentUrl);
                currentUrl = forward.top();
                forward.pop();
                cout << currentUrl << endl;
            }
        }
    }
}

int main()
{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    if (!(cin >> t))
        return 0;
    for (int i = 1; i <= t; ++i)
    {
        solve(i);
    }
    return 0;
}
