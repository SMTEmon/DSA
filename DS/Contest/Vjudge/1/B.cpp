//
// Created by SMTEmon.
//

// The Blocks Problem

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<stack<int>> blocks(n);
    vector<int> current_position(n);

    for (int i = 0; i < n; i++)
    {
        blocks[i].push(i);
        current_position[i] = i;
    }

    string inn, mode;
    cin >> inn;

    while (inn != "quit")
    {
        int from, to;
        cin >> from >> mode >> to;

        int cp_from = current_position[from];
        int cp_to = current_position[to];

        if (inn == "move" && cp_from != cp_to)
        {
            if (mode == "onto")
            {
                while (blocks[cp_from].top() != from &&
                       blocks[cp_from].size() > 0)
                {
                    int top_now = blocks[cp_from].top();
                    blocks[cp_from].pop();
                    blocks[top_now].push(top_now);
                    current_position[top_now] = top_now;
                }
                while (blocks[cp_to].top() != to &&
                       blocks[cp_to].size() > 0)
                {
                    int top_now = blocks[cp_to].top();
                    blocks[cp_to].pop();
                    blocks[top_now].push(top_now);
                    current_position[top_now] = top_now;
                }
                // Done with moving the top of stack here

                blocks[cp_to].push(from);
                blocks[cp_from].pop();
                current_position[from] = cp_to;
            }
        }

        cin >> inn;
    }

    return 0;
}