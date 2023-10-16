#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

/**
 * https://cses.fi/problemset/task/1668
 *
 * 2-coloring.
 * Run BFS and if current and any neighbor has the same color -> IMPOSSIBLE
 * Otherwise, keep coloring different colors!
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> team(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (team[i] != 0)
            continue;
        queue<int> q;
        q.push(i);
        team[i] = 1;

        while (!q.empty())
        {
            int f = q.front();
            q.pop();

            for (int neighbor : graph[f])
            {
                if (team[neighbor] == 0)
                {
                    int assigned_team = 0;
                    if (team[f] == 1)
                    {
                        assigned_team = 2;
                    }
                    else
                    {
                        assigned_team = 1;
                    }
                    team[neighbor] = assigned_team;
                    q.push(neighbor);
                }
                else
                {
                    if (team[neighbor] == team[f])
                    {
                        cout << "IMPOSSIBLE";
                        return 0;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << team[i] << " ";
    }

    return 0;
}