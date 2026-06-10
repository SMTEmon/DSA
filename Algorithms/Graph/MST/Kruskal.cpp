//
// Created by SMTEmon.
//

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

    Graph(lli nodeCount)
    {
        this->nodeCount = nodeCount;
        adj.resize(nodeCount);
    }

    void addEdge(lli src, lli dest, lli weight)
    {
        adj[src].push_back(make_pair(weight, dest));
        adj[dest].push_back(make_pair(weight, src));
    }

    lli kruskal()
    {
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

        DSU dsu(nodeCount);
        lli cost = 0, count = 0;

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
        }
        return cost;
    }
};

// gemini generated

int main()
{
    // Optimizing input/output operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lli numNodes, numEdges;
    if (!(cin >> numNodes >> numEdges))
        return 0;

    Graph g(numNodes);

    for (lli i = 0; i < numEdges; i++)
    {
        lli src, dest, weight;
        cin >> src >> dest >> weight;
        g.addEdge(src, dest, weight);
    }

    lli totalMSTCost = g.kruskal();
    cout << "Minimum Spanning Tree Cost: " << totalMSTCost << "\n";

    return 0;
}