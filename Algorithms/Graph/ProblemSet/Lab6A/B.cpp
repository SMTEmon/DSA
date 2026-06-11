//
// Created by SMTEmon.
//

// Data Center Disaster

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

class Graph
{
public:
    lli nodeCount;
    vector<vector<pair<lli, lli>>> adj;
    Graph(lli nodeCount)
    {
        this->nodeCount = nodeCount;
        adj.resize(nodeCount);
    }

    void add_edges(lli u, lli v, lli weight)
    {
        u--;
        v--;
        adj[u].push_back(make_pair(weight, v));

        // undirected
        adj[v].push_back(make_pair(weight, u));
    }

    lli prims(lli src)
    {
        lli res = 0;

        vector<lli> cost(nodeCount, INT_MAX);
        vector<bool> visited(nodeCount, false);

        priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq;

        pq.push(make_pair(0, src));
        cost[src] = 0;

        while (!pq.empty())
        {
            pair<lli, lli> node = pq.top();
            lli dest = node.second;
            pq.pop();
            if (visited[dest])
                continue;
            visited[dest] = true;
            res += node.first;

            for (pair<lli, lli> nei : adj[dest])
            {

                if (cost[dest] != INT_MAX && cost[nei.second] > nei.first)
                {

                    if (!visited[nei.second])
                    {
                        cost[nei.second] = nei.first;

                        pq.push(make_pair(cost[nei.second], nei.second));
                    }
                }
            }
        }

        for (bool i : visited)
        {
            if (!i)
                return -1;
        }
        return res;
    }
};

int main()
{
    lli n, m;
    cin >> n >> m;

    Graph g(n);

    for (lli i = 0; i < m; i++)
    {
        lli u, v, w;
        cin >> u >> v >> w;

        g.add_edges(u, v, w);
    }

    lli res = g.prims(0);

    if (res != -1)
        cout << res;
    else
        cout << "IMPOSSIBLE";
}