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
 * https://cses.fi/problemset/task/1136/
 *
 * LCA of all pairs
 *
 * Delta array in Tree!
 *
 * Counting at each position => Maybe delta?
 * If we know from L to R, we have to add 1, we don't have to go through all L ~ R and add 1
 * Just record, +1 at L, -1 at R.
 * Then prefix will result in the total count!
 *
 * Now, use this in tree.
 * When counting the frequency of node in path A ~ B.
 * We know, from each A ~ LCA and B ~ LCA, increase the cnt by one, (LCA should not increased twice)
 *
 * Thus using delta, just do delta[A]++, delta[B]++,
 * delta[lca]-- (prefix will +2 from lca since +1 is coming from A and B. Since LCA should be increased by one, offset it by -1),
 * delta[parent[lca]]-- (Since from parent of lca, the prefix sum should be 0. In order to offset the effect from A and B, we need to accum -2.
 *                       However we already did -1 at lca, so we only need to -1 at parent of lca to get net effect 0 from parent.)
 *
 * Now, how to get the count per node?
 * Subtree sum will give us the answer.
 * Just like prefix array, we calculate prefix at each node by using a subtree sum.
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
        if (child != prev)
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

long sumUpCnt(vector<vector<int>> &graph, int cur, int prev, vector<long> &delta)
{
    long sum = delta[cur];
    for (int child : graph[cur])
    {
        if (child != prev)
        {
            sum += sumUpCnt(graph, child, cur, delta);
        }
    }

    delta[cur] = sum;
    return sum;
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
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> depth(n + 1);
    vector<vector<int>> ancestor(n + 1, vector<int>(20, 0));
    vector<long> delta(n + 1, 0);
    dfs(graph, ancestor, depth, 1, 1, 0);

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        int lca = getLCA(graph, ancestor, depth, a, b);
        delta[a]++;
        delta[b]++;
        delta[lca]--;
        if (ancestor[lca][0] != 0 && ancestor[lca][0] != lca) // 1's parent is 1 in ancestor..
            delta[ancestor[lca][0]]--;
    }

    // for (int i = 1; i <= n; i++)
    // {
    //   cout << delta[i] << " ";
    // }

    sumUpCnt(graph, 1, -1, delta);

    for (int i = 1; i <= n; i++)
    {
        cout << delta[i] << " ";
    }

    return 0;
}