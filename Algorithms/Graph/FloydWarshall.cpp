//
// Created by SMTEmon.
//

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
        adj[u].push_back(make_pair(weight, v));

        // undirected
        adj[v].push_back(make_pair(weight, u));
    }

    vector<vector<lli>> fw()
    {

        vector<vector<lli>> dis(nodeCount, vector<lli>(nodeCount, INT_MAX));

        for (lli i = 0; i < nodeCount; i++)
        {
            dis[i][i] = 0;
        }

        lli source = 0;

        for (lli source = 0; source < nodeCount; source++)
        {
            vector<pair<lli, lli>> edges = adj[source];
            for (pair<lli, lli> edge : edges)
            {
                lli weight = edge.first;
                lli dest = edge.second;

                dis[source][dest] = weight;
            }
        }

        for (lli k = 0; k < nodeCount; k++)
        {
            for (lli i = 0; i < nodeCount; i++)
            {
                for (lli j = 0; j < nodeCount; j++)
                {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
        return dis;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lli nodes, edges;
    if (!(cin >> nodes >> edges))
        return 0;

    Graph g(nodes);

    for (lli i = 0; i < edges; i++)
    {
        lli u, v, w;
        cin >> u >> v >> w;
        g.add_edges(u, v, w);
    }

    vector<vector<lli>> dist = g.fw();

    for (lli i = 0; i < nodes; i++)
    {
        for (lli j = 0; j < nodes; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}