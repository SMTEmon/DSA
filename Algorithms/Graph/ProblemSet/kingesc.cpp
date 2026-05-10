// https://codeforces.com/problemset/problem/1033/A

//
// Created by SMTEmon.
//

#include <bits/stdc++.h>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adj;

    void dfs(vector<bool> &visited, vector<bool> &in_stack, bool &found, int node, int target)
    {
        visited[node] = false;
        for (int nei : adj[node])
        {
            if (!visited[nei])
            {
                if (in_stack[nei])
                    continue;
                else
                    dfs(visited, in_stack, found, nei, target);
            }
        }
        in_stack[node] = 0;
        if (node == target)
            found = true;
        return;
    }

public:
    void add_edge(int u, int v) // u -> v
    {
        adj[u].push_back(v);
    }

    bool dfs(int node, int target)
    {
        size_t sizee = adj.size();
        vector<bool> visited(sizee, false);
        vector<bool> in_stack(sizee, false);
        // stack<int> out;
        bool found = false;

        dfs(visited, in_stack, found, node, target);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int dimension;
    cin >> dimension;

    

    return 0;
}