// getting TLE
// https://cses.fi/problemset/task/1666

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

class DSU
{
    vector<int> parent, rnk;

public:
    DSU(int n)
    {
        parent.resize(n);
        rnk.resize(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i)
    {
        return parent[i] == i ? i : parent[i] = find(parent[i]);
    }

    void unite(int x, int y)
    {
        int a = find(x), b = find(y);
        if (a == b)
            return;
        if (rnk[a] < rnk[b])
            parent[a] = b;
        else if (rnk[a] > rnk[b])
            parent[b] = a;
        else
        {
            parent[b] = a;
            rnk[a]++;
        }
    }
};

int kruskal(int n, vector<pair<int, int>> &prev_edges, vector<pair<int, int>> &rec)
{
    DSU dsu(n);
    int count = 0;
    for (auto e : prev_edges)
    {
        int x = e.first, y = e.second;
        dsu.unite(x, y);
    }
    for (auto e : prev_edges)
    {
        int i = e.first;
        for (int j = 0; j < n; j++)
        {
            if (dsu.find(i) != dsu.find(j))
            {
                dsu.unite(i, j);
                rec.push_back({i, j});
                if (++count == n - 1)
                    break;
            }
        }
    }
    return count;
}

int main()
{
    int n, m;
    cin >> n >> m;

    // what i think we need
    // study how the implementation works, need to change the implementation for the problems, not just apply the implementation

    vector<pair<int, int>> rec, prev_edges;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        prev_edges.push_back({--x, --y});
    }

    int count = kruskal(n, prev_edges, rec);

    cout << count << "\n";

    for (auto e : rec)
    {
        cout << ++e.first << " " << ++e.second << "\n";
    }
}