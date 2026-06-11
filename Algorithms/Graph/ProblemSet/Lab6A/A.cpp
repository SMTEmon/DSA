//
// Created by SMTEmon.
//

// Logistics Network

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

    vector<vector<lli>> fw(vector<vector<lli>> &dis, vector<lli> ks)
    {

        // vector<vector<lli>> dis(nodeCount, vector<lli>(nodeCount, INT_MAX));

        // for (lli i = 0; i < nodeCount; i++)
        // {
        //     dis[i][i] = 0;
        // }

        // lli source = 0;

        // for (lli source = 0; source < nodeCount; source++)
        // {
        //     vector<pair<lli, lli>> edges = adj[source];
        //     for (pair<lli, lli> edge : edges)
        //     {
        //         lli weight = edge.first;
        //         lli dest = edge.second;

        //         dis[source][dest] = min(dis[source][dest], weight); // in case theres multiple edges between same sets of vertices
        //     }
        // }

        vector<int> open;

        for (lli k : ks)
        {
            for (lli i = 0; i < nodeCount; i++)
            {
                for (lli j = 0; j < nodeCount; j++)
                {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
            open.push_back(k);

            lli sum = 0;

            for (lli i : open)
            {
                for (lli j : open)
                {
                    sum += dis[i][j];
                }
            }
            cout << sum << " ";
        }
        return dis;
    }
};

int main()
{

    lli n;
    cin >> n;

    vector<vector<lli>> dis(n, vector<lli>(n, 0));

    for (lli i = 0; i < n; i++)
    {
        for (lli j = 0; j < n; j++)
        {
            cin >> dis[i][j];
        }
    }

    vector<lli> ks(n);

    for (lli i = 0; i < n; i++)
    {
        cin >> ks[i];
        --ks[i];
    }

    Graph g(n);
    g.fw(dis, ks);

    vector<int> open;

    // for (lli k = 0; k < n; k++)
    // {
    //     open.push_back(ks[k]);

    //     lli sum = 0;

    //     for (lli i : open)
    //     {
    //         for (lli j : open)
    //         {
    //             sum += dis[i][j];
    //         }
    //     }
    //     cout << sum << " ";
    // }
    // cout << endl;

    // for (lli i = 0; i < n; i++)
    // {
    //     for (lli j = 0; j < n; j++)
    //     {
    //         cout << dis[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}