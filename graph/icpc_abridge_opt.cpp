#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * This graph is basiacally directed tree! + DP
 *
 * As we go down, we accumulate the accumulated distance (pages) to current node from the root to dist[].
 *                and at the end(leaf), update minChildren path
 * As we go up (After we return from each child's dfs), record the top two min paths.
 *
 * When we select top two min paths, choose the path from the single path which is not merged.
 * For two paths, merge them (cost of one child + cost of second child - cost so far(LCA's cost)), and compare to current answer.
 *
 * Iterate all paths
 *  At each Node,
 *      1) Record the best single path, so that parent can use this path
 *      2) merge two best single path, and merge them
 *
 * This way we can consider all possible combination of paths!
 *
 * Dont record visited cuz I want to explore all paths from root
 */

struct Path
{
    int single = INT_MAX; // minimum single path
    int merge = INT_MAX;  // minimum combined path
};

void dfs(vector<vector<int>> &graph, vector<Path> &minChildren, vector<int> &dist, vector<int> &pages, int cur, int &ans)
{
    int firstMin = INT_MAX;
    int secMin = INT_MAX;
    for (int child : graph[cur])
    {
        dist[child] = dist[cur] + pages[child]; // record distance. dist[child] is the cumulated pages from the root
        // cout << "DIstance of " << child << " " << dist[child] << endl;
        dfs(graph, minChildren, dist, pages, child, ans);
        if (minChildren[child].single < firstMin) // select two minimum paths.
        {
            secMin = firstMin;
            firstMin = minChildren[child].single;
        }
        else if (minChildren[child].single < secMin)
        {
            secMin = minChildren[child].single;
        }
    }

    if (graph[cur].size() == 0) // leaf node
    {
        minChildren[cur].single = dist[cur]; // update the minimum path at the leaf! -> this is the distance from the root.
                                             // Therefore, we dont need to modify this or something. Also, do not update to min because
                                             // this should be the result of current path. not mixed with other paths.
        return;
    }

    minChildren[cur].single = firstMin; // get a single path that is smallest
    if (secMin != INT_MAX)
        minChildren[cur].merge = firstMin + secMin - dist[cur]; // this is merged min at current node.

    ans = min(ans, minChildren[cur].merge); // update to merged one. All paths are merged at some point(at root worst case), so just update to merge!
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<int> pages(n + 1, 0);
    vector<vector<int>> graph(n + 1);
    vector<unsigned long> minCost(n + 1, INT_MAX);
    vector<Path> minChildren(n + 1);
    vector<int> dist(n + 1, 0);
    vector<int> ind(n + 1, 0);

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> pages[i];
    }
    for (int i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        ind[to]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (ind[i] == 0)
        {
            graph[0].push_back(i);
        }
    }
    int ans = INT_MAX;
    dfs(graph, minChildren, dist, pages, 0, ans);

    cout << ans << "\n";

    return 0;
}