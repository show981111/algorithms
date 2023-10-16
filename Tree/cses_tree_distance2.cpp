#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

/**
 * https://cses.fi/problemset/task/1133/
 * Calculate for each node [the sum of the distances] from the node to all other nodes.
 *
 * Brute Force: O(N^2). Do dfs from each node.
 *
 * Let's use DP!
 * Key is, we can perfrom DFS twice! Get what we need from first pass, and calculate
 * final answer during second pass.
 *
 * If we have a sum for parent, we can do,
 * DIST_SUM(PAR) + (N - TreeSize[cur])                          - TreeSize[cur]
 *               move one step away from this number of nodes   move one step closer to this number of nodes
 *
 * Thus, computer DIST_SUM & TreeSize from first pass, and compute dist_sum for each node at second pass
 *
 * Can we do this in one pass?
 * At each node, we need dist_sum of parent & current subtree size
 *
 * subtree size is also available after we return from children -> Should wait until we return from children
 * dist_sum of parent should be passed in, but dist_sum of parent is not availabe until we return to parent.
 * So cannot do this in one pass
 */

int calDistSumFromCurAndRecordTreeSize(vector<vector<int>> &graph, vector<unsigned long> &distSum, vector<int> &treeSize, int curDist, int cur, int prev, const int from)
{
    distSum[from] += curDist;

    int size = 1; // for current node

    for (int child : graph[cur])
    {
        if (child == prev)
            continue;
        size += calDistSumFromCurAndRecordTreeSize(graph, distSum, treeSize, curDist + 1, child, cur, from);
    }

    treeSize[cur] = size;

    return size;
}

void calDistSumForAllNodes(vector<vector<int>> &graph, vector<unsigned long> &distSum, vector<int> &treeSize, int cur, int prev)
{
    unsigned long wholeTreeSize = graph.size() - 1;

    if (prev != -1)
        distSum[cur] = distSum[prev] + (wholeTreeSize - treeSize[cur]) - treeSize[cur];

    for (int child : graph[cur])
    {
        if (child == prev)
            continue;
        calDistSumForAllNodes(graph, distSum, treeSize, child, cur);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);
    vector<unsigned long> distSum(n + 1, 0);
    vector<int> treeSize(n + 1, 0);

    for (int i = 1; i <= n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    calDistSumFromCurAndRecordTreeSize(graph, distSum, treeSize, 0, 1, -1, 1);
    calDistSumForAllNodes(graph, distSum, treeSize, 1, -1);

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << treeSize[i] << " ";
    // }
    // cout << endl;
    // 6 9 5 8 8
    for (int i = 1; i <= n; i++)
    {
        cout << distSum[i] << " ";
    }
    return 0;
}