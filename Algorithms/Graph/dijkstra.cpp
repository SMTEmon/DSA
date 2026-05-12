#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    int nodeCount;
    vector<vector<pair<int, int>>> adj;
    Graph(int nodeCount)
    {
        this->nodeCount = nodeCount;
        adj.resize(nodeCount);
    }

    void add_edges(int u, int v, int weight)
    {
        adj[u].push_back(make_pair(weight, v));

        // undirected
        adj[v].push_back(make_pair(weight, u));
    }

    vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src)
    {
        vector<int> dis(nodeCount, INT_MAX);
        vector<bool> visited(nodeCount, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push(make_pair(0, src));
        dis[src] = 0;

        while (!pq.empty())
        {
            pair<int, int> node = pq.top();
            pq.pop();
            visited[node.second] = true;

            for (pair<int, int> nei : adj[node.second])
            {
                if (!visited[nei.second])
                    pq.push(nei);
                if (dis[nei.second] > (dis[node.second] + nei.first))
                {
                    dis[nei.second] = dis[node.second] + nei.first;
                }
            }
        }
        return dis;
    }
};

int main()
{
    // Test Case: A small graph with 5 nodes (0 to 4)
    // 0 --(1)--> 1 --(2)--> 2
    // |          |          ^
    // (4)        (2)        |
    // |          v          (1)
    // 4 --(3)--> 3 ---------|

    Graph g(5);
    g.add_edges(0, 1, 1);
    g.add_edges(0, 4, 4);
    g.add_edges(1, 2, 2);
    g.add_edges(1, 3, 2);
    g.add_edges(3, 4, 3);
    g.add_edges(3, 2, 1);

    int source = 0;
    vector<int> distances = g.dijkstra(g.adj, source);

    cout << "Shortest distances from node " << source << ":" << endl;
    for (int i = 0; i < distances.size(); i++)
    {
        cout << "Node " << i << " : ";
        if (distances[i] == INT_MAX)
            cout << "INF" << endl;
        else
            cout << distances[i] << endl;
    }

    return 0;
}