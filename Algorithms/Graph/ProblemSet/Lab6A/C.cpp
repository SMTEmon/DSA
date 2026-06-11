//
// Created by SMTEmon.
//

// Priority Cables

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

bool comp_for_adj(vector<lli> &a, vector<lli> &b)
{
    return a[2] < b[2];
}

class DSU
{
    vector<lli> parent, rank;

public:
    DSU(lli n)
    {
        parent.resize(n);
        rank.resize(n);
        for (lli i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    lli find(lli node)
    {
        return (parent[node] == node) ? node : (parent[node] = find(parent[node]));
    }

    void unite(lli u, lli v)
    {
        lli p1 = find(u);
        lli p2 = find(v);

        if (p1 != p2)
        {
            if (rank[p1] < rank[p2])
                parent[p1] = p2;
            else if (rank[p1] > rank[p2])
                parent[p2] = p1;
            else
            {
                parent[p2] = p1;
                rank[p1]++;
            }
        }
    }
};

class Graph
{

public:
    lli nodeCount;
    vector<vector<pair<lli, lli>>> adj;
    vector<vector<lli>> critical_edges;

    Graph(lli nodeCount)
    {
        this->nodeCount = nodeCount;
        adj.resize(nodeCount);
    }

    void addEdge(lli src, lli dest, lli weight, lli p)
    {
        src--;
        dest--;
        if (p == 1)
            critical_edges.push_back({src, dest, weight});
        else
        {
            adj[src].push_back(make_pair(weight, dest));
            adj[dest].push_back(make_pair(weight, src));
        }
    }

    lli kruskal()
    {

        DSU dsu(nodeCount);
        lli cost = 0, count = 0;

        for (vector<lli> edge : critical_edges)
        {
            int u = edge[0], v = edge[1], w = edge[2];

            if (dsu.find(u) != dsu.find(v))
            {
                dsu.unite(u, v);
                cost += w;
            }
            else if (++count == nodeCount - 1)
                return -1;
            else
                return -1;
        }

        vector<vector<lli>> edge_list; // u, v, w

        // creating a edge list first
        for (lli src = 0; src < nodeCount; src++)
        {
            vector<pair<lli, lli>> edges = adj[src];
            for (pair<lli, lli> edge : edges)
            {
                lli weight = edge.first;
                lli dest = edge.second;

                edge_list.push_back({src, dest, weight});
            }
        }

        sort(edge_list.begin(), edge_list.end(), comp_for_adj);

        for (vector<lli> edge : edge_list)
        {
            int u = edge[0], v = edge[1], w = edge[2];

            if (dsu.find(u) != dsu.find(v))
            {
                dsu.unite(u, v);
                cost += w;
                if (++count == nodeCount - 1)
                    break;
            }
            // else
            //     return -1;
        }
        return cost;
    }
};

int main()
{
    lli n, m;
    cin >> n >> m;

    Graph g(n);
    vector<bool> priority;

    for (lli i = 0; i < m; i++)
    {
        lli u, v, w, p;
        cin >> u >> v >> w >> p;

        g.addEdge(u, v, w, p);
    }

    lli res = g.kruskal();

    if (res != -1)
        cout << res;
    else
        cout << "IMPOSSIBLE";
}