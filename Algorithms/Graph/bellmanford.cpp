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
        // considering directed graph to keep negative edge compatibility

        adj[u].push_back(make_pair(weight, v));
    }

    vector<int> bellford(int start)
    {
        vector<int> dis(nodeCount, INT_MAX);

        dis[start] = 0;

        for (int i = 0; i < nodeCount; i++)
        {
            int u = 0;
            bool changed = false;
            for (vector<pair<int, int>> edges : adj)
            {
                for (pair<int, int> edge : edges)
                {
                    int weight = edge.first;
                    int v = edge.second;

                    if (dis[u] != INT_MAX && dis[v] > dis[u] + weight)
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
                return vector<int>(1, -1);
        }
        return dis;
    }
};

// Normal Graph
// int main()
// {
//     // Create a graph with 4 nodes (0, 1, 2, 3)
//     int nodes = 4;
//     Graph g(nodes);

//     // Add edges: (u, v, weight)
//     g.add_edges(0, 1, 1);
//     g.add_edges(1, 2, 3);
//     g.add_edges(2, 3, 2);
//     g.add_edges(0, 3, 10); // Longer direct path from 0 -> 3

//     int start_node = 0;
//     cout << "Running Bellman-Ford from node " << start_node << "..." << endl;

//     vector<int> distances = g.bellford(start_node);

//     // Check if a negative cycle was reported
//     if (distances.size() == 1 && distances[0] == -1)
//     {
//         cout << "Negative cycle detected!" << endl;
//     }
//     else
//     {
//         cout << "\nShortest distances from node " << start_node << ":" << endl;
//         for (int i = 0; i < g.nodeCount; i++)
//         {
//             cout << "To node " << i << ": ";
//             if (distances[i] == INT_MAX)
//             {
//                 cout << "INF (Unreachable)" << endl;
//             }
//             else
//             {
//                 cout << distances[i] << endl;
//             }
//         }

//         // Expected correct outputs after you fix the bugs:
//         // To node 0: 0
//         // To node 1: 1
//         // To node 2: 4  (0 -> 1 -> 2)
//         // To node 3: 6  (0 -> 1 -> 2 -> 3) instead of the direct path 10
//     }

//     return 0;
// }

// negative cycle
int main()
{
    // 4 nodes total (0, 1, 2, 3)
    int nodes = 4;
    Graph g(nodes);

    // Normal edge to get into the graph components
    g.add_edges(0, 1, 5);

    // Creating the negative cycle: 1 -> 2 -> 3 -> 1
    g.add_edges(1, 2, 2);
    g.add_edges(2, 3, 3);
    g.add_edges(3, 1, -8); // Total cycle cost: 2 + 3 - 8 = -3

    int start_node = 0;
    cout << "Running Bellman-Ford from node " << start_node << " on a negative cycle graph..." << endl;

    vector<int> distances = g.bellford(start_node);

    // Verifying your detection block
    if (distances.size() == 1 && distances[0] == -1)
    {
        cout << "SUCCESS: Negative cycle detected!" << endl;
    }
    else
    {
        cout << "FAILURE: The algorithm did not flag the negative cycle." << endl;
        cout << "Current distances array output: ";
        for (int d : distances)
        {
            if (d == INT_MAX)
                cout << "INF ";
            else
                cout << d << " ";
        }
        cout << endl;
    }

    return 0;
}