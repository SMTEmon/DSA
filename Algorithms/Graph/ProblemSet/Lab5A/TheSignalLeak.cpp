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
        // considering directed graph to keep negative edge compatibility

        adj[u].push_back(make_pair(weight, v));
    }

    vector<lli> bellford(lli start, bool &hasNegCycle)
    {
        start--;
        vector<lli> dis(nodeCount, LLONG_MAX);

        dis[start] = 0;

        for (lli i = 0; i < nodeCount; i++)
        {
            lli u = 0;
            bool changed = false;
            for (vector<pair<lli, lli>> edges : adj)
            {
                for (pair<lli, lli> edge : edges)
                {
                    lli weight = edge.first;
                    lli v = edge.second;

                    if (dis[u] != LLONG_MAX && dis[v] > dis[u] + weight)
                    {
                        changed = true;
                        dis[v] = dis[u] + weight;
                    }
                }

                u += 1;
            }

            if (!changed)
                break;

            if (i == nodeCount - 1)
                hasNegCycle = true;
        }
        return dis;
    }
};

int main()
{
    lli n, m, s;
    cin >> n >> m >> s;

    Graph G(n);

    for (lli i = 0; i < m; i++)
    {
        lli u, v, w;
        cin >> u >> v >> w;

        G.add_edges(u, v, w);
    }

    bool hasNegCycle = false;

    vector<lli> dis = G.bellford(s, hasNegCycle);

    for (int i = 0; i < n; i++)
    {
        if (hasNegCycle && dis[i] < 0)
            cout << "-INF" << endl;
        else if (dis[i] == LLONG_MAX)
            cout << "INF" << endl;
        else
            cout << dis[i] << endl;
    }
}