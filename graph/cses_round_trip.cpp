#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

/**
 * https://cses.fi/problemset/task/1669/
 *
 * Cycle detection using DFS (Directed Graph) -> USE UNION-FIND for Undirected
 * If I visit the node that is already in the current path except parent, then that is a cycle!
 *
 * Using visited to check which node I have visited during this path,
 * and make it to false after dfs like BACKTRACKING!
 * ==> NO NEED FOR BACKTRACK! We keep visited vs current path visited separately
 *      If we already visited that node and that node is not in the current path?
 *          -> It is confirmed that that node is not making a cycle. -> CAN SKIP!
 *
 * visited_group(Connected Components) is the visited to check which node I have visited.
 * All nodes that I can visit from a single node using DFS are all connected and
 * if it doesn't have a cycle, then we can just skip the dfs for those nodes! (line 70)
 */

bool dfs(vector<vector<int>> &graph, int cur, int end, vector<int> &curPath, vector<bool> &visited, int prev, vector<bool> &visited_group)
{
    if (cur == end && curPath.size() >= 2)
        return true;

    for (int neighbor : graph[cur])
    {
        if (neighbor == prev)
            continue;
        if (visited[neighbor] == true)
        { // cycle. Not a parent but alr visited!
            curPath.push_back(neighbor);
            return true;
        }
        if (visited_group[neighbor]) // if we already visited and confirmed there is no cycle, can skip
            continue;
        visited_group[neighbor] = true;
        visited[neighbor] = true;
        curPath.push_back(neighbor);
        bool res = dfs(graph, neighbor, end, curPath, visited, cur, visited_group);
        if (res)
        {
            return true;
        }
        visited[neighbor] = false;
        curPath.pop_back();
    }

    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> visited_group(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        if (visited_group[i])
            continue;

        vector<int> curPath;
        vector<bool> visited(n + 1, false);
        curPath.push_back(i);
        visited_group[i] = true;
        visited[i] = true;
        if (dfs(graph, i, i, curPath, visited, -1, visited_group))
        {
            int from = curPath.back();
            auto fromIter = find(curPath.begin(), curPath.end(), from);
            cout << curPath.end() - fromIter << "\n";
            for (auto iter = fromIter; iter != curPath.end(); ++iter)
            {
                cout << *iter << " ";
            }
            return 0;
        }
    }

    cout << "IMPOSSIBLE";

    return 0;
}