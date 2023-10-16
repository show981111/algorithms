#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Tree diameter.
 *
 * (1) DFS
 * Two DFS can solve this.
 * From any node, find farthest node.
 * Then do DFS from that node.
 *
 * The reason is, always the end of the diameter should be the farthest node
 * from any nodes.
 *
 */

void dfs(vector<vector<int>> &tree, int from, int cur, int curLength, int &maxLength, int &farthest)
{
    curLength++;
    if (curLength > maxLength)
    {
        maxLength = curLength;
        farthest = cur;
    }
    for (int child : tree[cur])
    {
        if (child == from)
            continue;
        dfs(tree, cur, child, curLength, maxLength, farthest);
    }
}

/**
 * (2) DFS with recursion (Sort of divide and conquer, Solve it bottom-up fashion)
 * T(cur) = MAX((child A's depth + child B's depth - 2* current node's depth), (one max depth))
 * At each node X, two choices,
 * (A) Just pick one path from leaf (Distance from root ~ leaf) : straight path from root -> leaf
 * (B) Largest X ~ leaf + Second largest X ~ leaf - 2 * (root ~ X) : Path that starts from one leaf, go through X, to the other leaf of X.
 *
 * We can do this in O(N) by returning the largest depth from current path.
 *
 */

// T(cur) = (child A's depth + child B's depth - 2* current node's depth) or one max depth
// return depth
int dfs(vector<vector<int>> &tree, int from, int cur, int depth, int &maxLength)
{
    int first = 0, second = 0;

    if (tree[cur].size() == 1 && tree[cur][0] == from)
    {
        return depth;
    }

    for (int child : tree[cur])
    {
        if (child == from)
            continue;
        int childDepth = dfs(tree, cur, child, depth + 1, maxLength);
        if (first < childDepth)
        {
            second = first;
            first = childDepth;
        }
        else if (second < childDepth)
        {
            second = childDepth;
        }
    }

    maxLength = max(maxLength, first);
    if (second > 0)
    {
        maxLength = max(maxLength, first + second - 2 * depth);
    }

    return first;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<vector<int>> tree(n + 1);
    for (int i = 1; i <= n - 1; i++)
    {
        int from, to;
        cin >> from >> to;
        tree[from].push_back(to);
        tree[to].push_back(from);
    }
    int length = 0;
    dfs(tree, -1, 1, 0, length);
    cout << length << "\n";

    return 0;
}