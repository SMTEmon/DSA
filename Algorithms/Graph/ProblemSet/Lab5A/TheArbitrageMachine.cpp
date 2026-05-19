#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

class Graph
{
public:
    lli nodeCount;
    vector<vector<pair<double, lli>>> adj;

    Graph(lli nodeCount)
    {
        this->nodeCount = nodeCount;
        adj.resize(nodeCount);
    }

    void add_edges(lli u, lli v, double weight)
    {
        u--;
        v--;
        // considering directed graph to keep negative edge compatibility

        adj[u].push_back(make_pair(weight, v));
    }

    vector<double> bellford(lli start)
    {
        start--;
        vector<double> dis(nodeCount, LLONG_MAX);

        dis[start] = 0;

        for (lli i = 0; i < nodeCount; i++)
        {
            lli u = 0;
            bool changed = false;
            for (vector<pair<double, lli>> edges : adj)
            {
                for (pair<double, lli> edge : edges)
                {
                    double weight = edge.first;
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
                return vector<double>(1, -1);
        }
        return dis;
    }
};

int main()
{
    lli n, m;
    cin >> n >> m;

    Graph G(n);

    for (lli i = 0; i < m; i++)
    {
        lli u, v;
        double w;
        cin >> u >> v >> w;

        w = -log10(w);

        G.add_edges(u, v, w);
    }

    vector<double> dis = G.bellford(1);
    if (dis.size() == 1 && dis[0] == -1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}