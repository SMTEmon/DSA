//
// Created by SMTEmon.
//

// https://codeforces.com/contest/160/problem/D

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

class DSU
{
public:
    lli nodeCount;
    vector<lli> parent;
    vector<lli> rank;

    DSU(lli nodeCount)
    {
        this->nodeCount = nodeCount;
        parent.resize(nodeCount);
        rank.resize(nodeCount);

        for (lli i = 0; i < nodeCount; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    lli find(lli node)
    {
        return (parent[node] == node) ? node : (parent[node] = find(parent[node]));
    }

    lli unite(lli u, lli v)
    {
        lli parent_u = find(u), parent_v = find(v);
        if (parent_u != parent_v)
        {
            if (rank[parent_u] < rank[parent_v])
            {
                parent[parent_u] = parent_v;
            }
            else if (rank[parent_u] > rank[parent_v])
            {
                parent[parent_v] = parent_u;
            }
            else
            {
                parent[parent_u] = parent_v;
                rank[parent_v]++;
            }
        }
    }
};

class Graph
{
    lli nodeCount;
    lli edgeCount;
    vector<vector<lli>> edge_list;

    Graph(lli nodeCount, lli edgeCount)
    {
        this->nodeCount = nodeCount;
        this->edgeCount = edgeCount;
    }

    void add_edge(lli u, lli v, lli w)
    {
        edge_list.push_back({u, v, w, 0});
    }
};