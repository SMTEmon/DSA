// https://codeforces.com/problemset/problem/20/C

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;
const lli llMax = LLONG_MAX;

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

    vector<pair<lli, lli>> dijkstra(vector<vector<pair<lli, lli>>> &adj, lli src) //<dis, par>
    {
        src--;
        vector<pair<lli, lli>> dis(nodeCount, make_pair(llMax, -1));
        vector<bool> visited(nodeCount, false);

        priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq;

        pq.push(make_pair(0, src));
        dis[src].first = 0;

        while (!pq.empty())
        {
            pair<lli, lli> node = pq.top();
            pq.pop();
            if (visited[node.second])
                continue;
            visited[node.second] = true;

            for (pair<lli, lli> nei : adj[node.second])
            {

                if (dis[node.second].first != llMax && dis[nei.second].first > (dis[node.second].first + nei.first))
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
    lli N, M;
    cin >> N >> M;

    Graph route(N);

    for (lli i = 0; i < M; i++)
    {
        lli u, v, w;
        cin >> u >> v >> w;

        route.add_edges(u, v, w);
        // cout << u << v << w << endl;
    }

    vector<pair<lli, lli>> toDestination = route.dijkstra(route.adj, 1);

    lli maxx = INT_MIN;

    lli nodeNow = N - 1;

    stack<lli> shortestRoute;

    shortestRoute.push(N - 1);

    if (toDestination[nodeNow].second == -1)
    {
        cout << -1 << endl;
        return 0;
    }

    while (nodeNow != 0)
    {

        lli parent = toDestination[nodeNow].second;
        nodeNow = parent;
        shortestRoute.push(nodeNow);
    }

    lli sizeeOfStack = shortestRoute.size();

    for (lli i = 0; i < sizeeOfStack; i++)
    {
        cout << shortestRoute.top() + 1 << " ";
        shortestRoute.pop();
    }
}