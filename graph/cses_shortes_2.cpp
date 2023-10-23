#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
#include <unordered_set>
#include <limits>
#include <climits>
#include <cassert>
using namespace std;

/**
 * https://cses.fi/problemset/task/1672
 *
 *
 * Floyd–Warshall algorithm
 * Shortest distance from all nodes to all other noces. (O(N^3))
 *
 * Initialize distance matrix, and use the fact that dist(x,y) = dist(x,c) + dist(c,y)
 *
 * For all possible "c", we update the distance of all possible pairs of nodes (x,y)
 * So it is like DP.
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cities, roads, q;
    cin >> cities >> roads >> q;

    vector<vector<long>> dist(cities + 1, vector<long>(cities + 1, -1));
    for (int i = 0; i < roads; i++)
    {
        long a, b, d;
        cin >> a >> b >> d;
        dist[a][b] = dist[a][b] == -1 ? d : min(dist[a][b], d);
        dist[b][a] = dist[a][b];
    }

    for (int i = 1; i <= cities; i++)
    {
        dist[i][i] = 0;
    }

    for (int k = 1; k <= cities; k++)
    {
        for (int i = 1; i <= cities; i++)
        {
            for (int j = 1; j <= cities; j++)
            {
                long newDistance = dist[i][k] == -1 || dist[k][j] == -1 ? LONG_MAX : dist[i][k] + dist[k][j];
                if (dist[i][j] == -1 && newDistance < LONG_MAX)
                {
                    dist[i][j] = newDistance;
                }
                else
                    dist[i][j] = min(dist[i][j], newDistance);
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << dist[a][b] << "\n";
    }

    return 0;
}