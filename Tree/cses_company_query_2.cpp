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
 * https://cses.fi/problemset/task/1688
 *
 * LCA of all pairs
 * Using Binary Lifting.
 *
 * We have to 2^K_th power of ancestors from each node by O(nlogn) + Depth
 *
 * Brute force LCA from bottom up.
 * -> Hoist lower node up so that both node are in the same depth.
 *    Then, climb up one step at a time until they meet for the first time!
 *
 * Now, how can we use 2^K_th power ancestor to speed this up?
 * Climbing can be done in O(LogN) if we use binary lifting.
 *
 * 1) Make both node the same depth
 *    : climb by (higher Node - lower Node) using 2^K_th ancestor
 * 2) Finding LCA by climbing one step at a time
 *    : not one step, but climb 2^K_th step at a time like binary search
 *      If a != b after 2^K_th step, move them up.
 *      If a == b dont climb, record it as a possible LCA. (We should find the first point where a == b, this can go over this point)
 *      At each time reduce step by /2. Since we are dealing with 2^K, we can just reduce the power by 1 (k - 1)
 *
 * Different perspective of binary search.
 * Getting as close we can by reducing the amount of step we take each time!
 */

// record 2^k_th ancestor and depth!
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
        dfs(graph, ancestor, depth, child, cur, curDepth);
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

    // Using FOr loop
    // Imange, we are going as close as we can to the LCA.
    //
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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> graph(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;
        graph[p].push_back(i);
    }
    vector<int> depth(n + 1);
    vector<vector<int>> ancestor(n + 1, vector<int>(20, 0));
    dfs(graph, ancestor, depth, 1, 1, 0);

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << getLCA(graph, ancestor, depth, a, b) << "\n";
    }

    return 0;
}