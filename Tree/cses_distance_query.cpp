#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cassert>
using namespace std;

/**
 * https://cses.fi/problemset/task/1135/
 *
 * Distance between two nodes
 *
 * Distance between two nodes = depth[a] + depth[b] - 2*depth[LCA]
 * How do we get LCA? -> From K_th ancestor use binary lifting. (https://cses.fi/problemset/task/1688)
 *
 */

// PreOrder
void dfs(vector<vector<int>> &graph, vector<vector<int>> &ancestor, vector<int> &depth, int cur, int prev, int curDepth)
{
    depth[cur] = curDepth++;

    ancestor[cur][0] = prev; // base case
    int power = 1;
    while ((1 << power) < curDepth)
    {
        ancestor[cur][power] = ancestor[ancestor[cur][power - 1]][power - 1];
        power++;
    }

    for (int child : graph[cur])
    {
        if (child == prev)
            continue;
        dfs(graph, ancestor, depth, child, cur, curDepth);
    }
}

int getLCA(vector<vector<int>> &graph, vector<vector<int>> &ancestor, vector<int> &depth, int a, int b)
{
    if (depth[a] < depth[b])
    {
        swap(a, b); // now always b is higher that a
    }
    // depth[a] >= depth[b]

    int steps = depth[a] - depth[b];
    int power = 0;
    while (steps > 0) // make them same depth
    {
        if ((steps & 1) == 1)
        {
            a = ancestor[a][power];
        }
        power++;
        steps = steps >> 1;
    }
    // cout << depth[a] << "  " << depth[b] << " ";
    assert(depth[a] == depth[b]);
    if (a == b)
        return a;

    int low = depth[a];
    int high = 0;

    int gap = low - high;
    int step = 0;
    while (gap > 0)
    {
        step++;
        gap = gap >> 1;
    }

    int lca = -1;
    for (; step >= 0; step--)
    {
        if (ancestor[a][step] != ancestor[b][step])
        {
            a = ancestor[a][step];
            b = ancestor[b][step];
        }
        else
        {
            lca = ancestor[a][step];
        }
    }
    return lca;
}

int getDistance(vector<vector<int>> &graph, vector<vector<int>> &ancestor, vector<int> &depth, int a, int b)
{
    int lca = getLCA(graph, ancestor, depth, a, b);
    return depth[a] + depth[b] - 2 * depth[lca];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> depth(n + 1);
    vector<vector<int>> ancestor(n + 1, vector<int>(20, 0));
    dfs(graph, ancestor, depth, 1, -1, 0);

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << getDistance(graph, ancestor, depth, a, b) << "\n";
    }

    return 0;
}