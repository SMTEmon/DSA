

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
        u--;
        v--;
        adj[u].push_back(make_pair(weight, v));

        // undirected
        adj[v].push_back(make_pair(weight, u));
    }

    vector<pair<int, int>> dijkstra(vector<vector<pair<int, int>>> &adj, int src) //<dis, par>
    {
        src--;
        vector<pair<int, int>> dis(nodeCount, make_pair(INT_MAX, -1));
        vector<bool> visited(nodeCount, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push(make_pair(0, src));
        dis[src].first = 0;

        while (!pq.empty())
        {
            pair<int, int> node = pq.top();
            pq.pop();
            visited[node.second] = true;

            for (pair<int, int> nei : adj[node.second])
            {

                if (dis[node.second].first != INT_MAX && dis[nei.second].first > (dis[node.second].first + nei.first))
                {
                    dis[nei.second].first = dis[node.second].first + nei.first;
                    dis[nei.second].second = node.second;
                    if (!visited[nei.second])
                        pq.push(make_pair(dis[nei.second].first, nei.second));
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

    long long int N, M, S, D, C;
    cin >> N >> M;

    Graph route(N);

    for (long long int i = 0; i < M; i++)
    {
        long long int u, v, w;
        cin >> u >> v >> w;

        route.add_edges(u, v, w);
        // cout << u << v << w << endl;
    }

    vector<pair<int, int>> toDestination = route.dijkstra(route.adj, 1);

    long long int maxx = INT_MIN;

    long long int nodeNow = N - 1;

    while (nodeNow != 0)
    {
        long long int parent = toDestination[nodeNow].second;

        long long int cost = toDestination[nodeNow].first -
                             toDestination[parent].first;
        if (cost > maxx)
            maxx = cost;
        nodeNow = parent;
    }

    cout << maxx << endl;
}