// https://codeforces.com/problemset/problem/449/B

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

    vector<lli> dijkstra(vector<vector<pair<lli, lli>>> &adj, lli src)
    {
        src--;
        vector<lli> dis(nodeCount, LLONG_MAX);
        vector<bool> visited(nodeCount, false);

        priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq;

        pq.push(make_pair(0, src));
        dis[src] = 0;

        while (!pq.empty())
        {
            pair<lli, lli> node = pq.top();
            pq.pop();
            if (visited[node.second])
                continue;
            visited[node.second] = true;

            for (pair<lli, lli> nei : adj[node.second])
            {

                if (dis[node.second] != LLONG_MAX && dis[nei.second] > (dis[node.second] + nei.first))
                {
                    dis[nei.second] = dis[node.second] + nei.first;
                    if (!visited[nei.second])
                        pq.push(make_pair(dis[nei.second], nei.second));
                }
            }
        }
        return dis;
    }
};

int main()
{

    lli n, m, k;
    cin >> n >> m >> k;

    Graph route(n);

    for (lli i = 0; i < m; i++)
    {
        lli u, v, w;
        cin >> u >> v >> w;
        route.add_edges(u, v, w);
    }

    vector<lli> train_route(n, LLONG_MAX);

    lli count = 0;

    for (lli i = 0; i < k; i++)
    {
        lli s, x;
        cin >> s >> x;
        s--;

        if (train_route[s] != LLONG_MAX)
            count++; // if there was already a value, count++

        train_route[s] = min(x, train_route[s]);
    }

    vector<lli> dis = route.dijkstra(route.adj, 1);

    for (lli i = 0; i < n; i++)
    {
        if (train_route[i] != LLONG_MAX && dis[i] <= train_route[i])
            count++;
    }

    cout << count << endl;
}