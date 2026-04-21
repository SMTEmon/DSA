//
// Created by SMTEmon.
//

#include <bits/stdc++.h>

using namespace std;

// handle each test case
void solve(int caseNum)
{
    int n, m;
    cin >> n >> m;
    deque<int> dq;
    cout << "Case " << caseNum << ":\n";
    for (int i = 0; i < m; ++i)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "pushLeft")
        {
            int x;
            cin >> x;
            // check if full before pushing
            if ((int)dq.size() == n)
            {
                cout << "The queue is full\n";
            }
            else
            {
                dq.push_front(x);
                cout << "Pushed in left: " << x << "\n";
            }
        }
        else if (cmd == "pushRight")
        {
            int x;
            cin >> x;
            if ((int)dq.size() == n)
            {
                cout << "The queue is full\n";
            }
            else
            {
                dq.push_back(x);
                cout << "Pushed in right: " << x << "\n";
            }
        }
        else if (cmd == "popLeft")
        {
            // check if empty before popping
            if (dq.empty())
            {
                cout << "The queue is empty\n";
            }
            else
            {
                cout << "Popped from left: " << dq.front() << "\n";
                dq.pop_front();
            }
        }
        else if (cmd == "popRight")
        {
            if (dq.empty())
            {
                cout << "The queue is empty\n";
            }
            else
            {
                cout << "Popped from right: " << dq.back() << "\n";
                dq.pop_back();
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    if (!(cin >> t))
        return 0;
    for (int i = 1; i <= t; ++i)
    {
        solve(i);
    }
    return 0;
}