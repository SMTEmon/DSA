// https://cses.fi/problemset/task/1194

//
// Created by SMTEmon.
//

#include <bits/stdc++.h>

using namespace std;
using lli = long long int;

void solve(vector<vector<char>> mat, lli n, lli m)
{

    lli dx[] = {-1, 1, 0, 0};
    lli dy[] = {0, 0, 1, -1};

    // for Monsters

    vector<vector<lli>> bfsM(n, vector<lli>(m)); // res
    queue<pair<lli, lli>> qM;
    vector<vector<bool>> visM(n, vector<bool>(m));

    for (lli i = 0; i < n; i++)
    {
        for (lli j = 0; j < m; j++)
        {
            if (mat[i][j] == '#')
                bfsM[i][j] = -1;
            else if (mat[i][j] == 'M')
            {
                bfsM[i][j] = 0;
                qM.push(make_pair(i, j));
                visM[i][j] = true;
            }
            else if (mat[i][j] == '.' || mat[i][j] == 'A')
                bfsM[i][j] = INT_MAX;
        }
    }

    while (!qM.empty())
    {
        pair<lli, lli> now = qM.front();
        qM.pop();

        lli x = now.first, y = now.second;

        if (mat[x][y] == '#')
            continue;

        for (lli i = 0; i < 4; i++)
        {
            lli next_x = x + dx[i];
            lli next_y = y + dy[i];

            if (next_x < n && next_x >= 0 &&
                next_y < m && next_y >= 0)
            {
                if (mat[next_x][next_y] == '#')
                    continue;

                bfsM[next_x][next_y] = min(bfsM[next_x][next_y], bfsM[x][y] + 1);
                if (!visM[next_x][next_y])
                {
                    qM.push(make_pair(next_x, next_y));
                    visM[next_x][next_y] = true;
                }
            }
        }
    }

    // for me

    vector<vector<lli>> bfsA(n, vector<lli>(m)); // res
    queue<pair<lli, lli>> qA;
    vector<vector<char>> dir(n, vector<char>(m, '.'));

    for (lli i = 0; i < n; i++)
    {
        for (lli j = 0; j < m; j++)
        {
            if (mat[i][j] == '#')
            {
                bfsA[i][j] = -1;
            }
            else if (mat[i][j] == 'A')
            {
                bfsA[i][j] = 0;
                qA.push(make_pair(i, j));
                dir[i][j] = 'A';

                if (i == (n - 1) || i == 0 || j == (m - 1) || j == 0)
                {
                    cout << "YES" << "\n";
                    cout << 0 << "\n";
                    return;
                }
            }
            else if (mat[i][j] == '.' || mat[i][j] == 'M')
                bfsA[i][j] = INT_MAX;
        }
    }
    vector<vector<bool>> visA(n, vector<bool>(m));

    queue<pair<lli, lli>> escape; // holding escape pos

    while (!qA.empty())
    {
        pair<lli, lli> now = qA.front();
        qA.pop();

        lli x = now.first, y = now.second;
        if (mat[x][y] == '#')
            continue;

        for (lli i = 0; i < 4; i++)
        {
            lli next_x = x + dx[i];
            lli next_y = y + dy[i];
            if (next_x < n && next_x >= 0 &&
                next_y < m && next_y >= 0)
            {
                if (mat[next_x][next_y] == '#')
                    continue;

                if ((next_x == (n - 1) || next_x == 0) ||
                    (next_y == (m - 1) || next_y == 0))
                {
                    if (mat[next_x][next_y] != '#')
                        escape.push(make_pair(next_x, next_y));
                }

                if (bfsA[next_x][next_y] > bfsA[x][y] + 1)
                {
                    bfsA[next_x][next_y] = bfsA[x][y] + 1;

                    // lli dx[] = {-1, 1, 0, 0};
                    // lli dy[] = {0, 0, 1, -1};
                    if (bfsA[next_x][next_y] < bfsM[next_x][next_y])
                    {
                        if (i == 0)
                            dir[next_x][next_y] = 'U';
                        else if (i == 1)
                            dir[next_x][next_y] = 'D';
                        else if (i == 2)
                            dir[next_x][next_y] = 'R';
                        else if (i == 3)
                            dir[next_x][next_y] = 'L';

                        if (!visA[next_x][next_y])
                        {
                            qA.push(make_pair(next_x, next_y));
                            visA[next_x][next_y] = true;
                        }
                    }
                }

                bfsA[next_x][next_y] = min(bfsA[next_x][next_y], bfsA[x][y] + 1);
            }
        }
    }

    // reconstruct
    while (!escape.empty())
    {
        pair<lli, lli> now = escape.front();
        escape.pop();
        vector<char> moves;
        lli count = 0;

        while (mat[now.first][now.second] != 'A')
        {
            count++;
            lli i;
            lli x = now.first, y = now.second;

            if (dir[x][y] == 'D')
                i = 0;
            else if (dir[x][y] == 'U')
                i = 1;
            else if (dir[x][y] == 'L')
                i = 2;
            else if (dir[x][y] == 'R')
                i = 3;
            else
                break;

            moves.push_back(dir[x][y]);
            now = make_pair(x + dx[i], y + dy[i]);

            if (mat[now.first][now.second] == 'A')
            {
                cout << "YES" << endl;
                cout << count << endl;

                lli size_of_moves = moves.size();

                for (lli j = size_of_moves - 1; j >= 0; j--)
                {
                    cout << moves[j];
                }
                cout << "\n";
                return;
            }
        }
    }
    cout << "NO" << "\n";
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    lli n, m;
    cin >> n >> m;

    vector<vector<char>> mat(n, vector<char>(m));

    for (lli i = 0; i < n; i++)
    {
        for (lli j = 0; j < m; j++)
        {
            cin >> mat[i][j];
        }
    }

    solve(mat, n, m);

    return 0;
}