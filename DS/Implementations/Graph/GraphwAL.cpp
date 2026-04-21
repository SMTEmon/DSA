#include <bits/stdc++.h>

using namespace std;

class GraphwAL
{
    vector<vector<int>> adj_Nodes;
    int timer;

    void findBridgesAndArticulations(int u, int p, vector<int> &disc, vector<int> &low,
                                     vector<bool> &visited, vector<pair<int, int>> &bridges,
                                     set<int> &articulations)
    {
        visited[u] = true;
        disc[u] = low[u] = ++timer;
        int children = 0;

        for (int v : adj_Nodes[u])
        {
            if (v == p)
                continue;
            if (visited[v])
            {
                low[u] = min(low[u], disc[v]);
            }
            else
            {
                children++;
                findBridgesAndArticulations(v, u, disc, low, visited, bridges, articulations);
                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u])
                {
                    bridges.push_back({u, v});
                }

                if (p != -1 && low[v] >= disc[u])
                {
                    articulations.insert(u);
                }
            }
        }
        if (p == -1 && children > 1)
        {
            articulations.insert(u);
        }
    }

    void DFSUtil(int curr, vector<bool> &visited)
    {
        visited[curr] = true;
        cout << curr << " ";

        for (int nei : adj_Nodes[curr])
        {
            if (!visited[nei])
            {
                DFSUtil(nei, visited);
            }
        }
    }

public:
    GraphwAL(int n)
    {
        adj_Nodes = vector<vector<int>>(n);
    }
    void add_edge(int u, int v)
    {
        if (u >= adj_Nodes.size() || v >= adj_Nodes.size())
            adj_Nodes.resize(max(u, v) + 1);

        adj_Nodes[u].push_back(v);
        adj_Nodes[v].push_back(u);
    }

    void print_graph()
    {
        int size_of_adj = adj_Nodes.size();

        for (int node = 0; node < size_of_adj; node++)
        {
            int adj_nei = adj_Nodes[node].size();

            for (int nei = 0; nei < adj_nei; nei++)
            {
                cout << adj_Nodes[node][nei] << " ";
            }

            cout << "\n";
        }
    }

    void bfs(int startVer)
    {
        vector<bool> visited(adj_Nodes.size(), false);
        queue<int> q;

        visited[startVer] = true;
        q.push(startVer);

        cout << "BFS starting from: " << startVer << ": ";

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (int nei : adj_Nodes[curr])
            {
                if (!visited[nei])
                {
                    visited[nei] = true;
                    q.push(nei);
                }
            }
        }

        cout << "\n";
    }

    void DFSbyRec(int startt)
    {
        vector<bool> visited(adj_Nodes.size(), false);

        cout << "Starting DFS from " << startt << ": ";

        DFSUtil(startt, visited);

        cout << "\n";
    }

    void DFSbyIt(int startt)
    {
        vector<bool> visited(adj_Nodes.size(), false);

        stack<int> s;
        s.push(startt);

        cout << "Started DFS from " << startt << ": ";

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            if (!visited[curr])
            {
                visited[curr] = true;
                cout << curr << " ";
            }

            for (int nei : adj_Nodes[curr])
            {
                if (!visited[nei])
                {
                    s.push(nei);
                }
            }
        }

        cout << "\n";
    }

    void findBridgesAndCutVertices()
    {
        int n = adj_Nodes.size();
        vector<int> disc(n, -1), low(n, -1);
        vector<bool> visited(n, false);
        vector<pair<int, int>> bridges;
        set<int> articulations;
        timer = 0;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                findBridgesAndArticulations(i, -1, disc, low, visited, bridges, articulations);
            }
        }

        cout << "Bridges:\n";
        for (auto &b : bridges)
            cout << b.first << " -- " << b.second << "\n";

        cout << "Cut Vertices (Articulation Points):\n";
        for (int a : articulations)
            cout << a << " ";
        cout << "\n";
    }
};
