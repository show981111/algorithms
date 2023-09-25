#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Shortest distance in Undirected graph can be done with BFS
 *
 * Tracking the path of BFS can be done by recording the parent node
 * We can use parents array like a visited array. why?
 *
 * If the parent is already assigned, that means that node is already visited.
 * Always, the first parent that reaches that node is the shortes path. Because
 * BFS visits node level-by-level. Thus, first one who reaches that node should
 * be the shortest one.
 *
 * Directed? -> Dijkstra, bellman ford etc..
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;

    cin >> n >> m;
    vector<vector<int>> graph(n + 1); // 1-indexed
    vector<int> parents(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    queue<int> q;
    q.push(1);
    parents[1] = 1;
    bool found = false;

    while (!q.empty())
    {
        int f = q.front();
        q.pop();

        // cout << f << " ";

        for (int neighbor : graph[f])
        {
            if (parents[neighbor] == 0)
            {
                parents[neighbor] = f;
                if (neighbor == n)
                {
                    found = true;
                    break;
                }
                q.push(neighbor);
            }
        }
        if (found)
            break;
    }

    if (found)
    {
        vector<int> path;
        int cur = n;
        while (cur != 1)
        {
            path.push_back(cur);
            cur = parents[cur];
        }
        path.push_back(1);
        cout << path.size() << "\n";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << path[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}