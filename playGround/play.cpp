#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_set>
using namespace std;

/**
 * First trial similar to LIS approach (Edge including this!)
 *   Doesn't work. Due to tie breaker. When tere are multiple ways to build a maximum matching set,
 *   We don't know which one to use. ex) there is A, B, C way for T(I). and later adding T(I+1), A and E_i+1 might not work but B and E_i+1
 *   might work and we miss the count og B + E_i+1, if we chose A way.
 *   => Adding I_th edge to T(J) should be independant from the ways we can build T(J)!!
 *
 * Second Trial Tree Traversal Using DFS.
 *
 * Key point is, at each node we have two choice
 * 1) dont choose any edge between current node to children. Just sum up all max_matching of all children. SUM(max_matching(x_i) ~ max_matching(x_j))
 * 2) Choose one edge between current to one child. Then, we should choose the children's sum of chosen node.
 *      If we chose x_i, 1 + sum(max_matching(x_i's children)) + sum(max_matching(x_0) ~ max_matching(x_i-1),max_matching(x_i+1) ~ max_matching(x_j))
 * Choose max!
 *
 * So what we should return from dfs? -> sum of children(1, not including current node) & currentSum(2, including current node)
 */

// return sum of children + current sum
pair<int, int> dfs(vector<vector<int>> &graph, int cur, int parent, int &ans)
{
    int sumOfChildren = 0;
    int currentSum = 0;
    vector<pair<int, int>> temp;
    for (int child : graph[cur])
    {
        if (child == parent)
            continue;

        pair<int, int> childRes = dfs(graph, child, cur, ans);
        sumOfChildren += childRes.second;
        temp.push_back(childRes);
    }
    if (temp.size() == 0)
    { // leaf
        return {0, 0};
    }
    ans = max(ans, sumOfChildren); // not including any edge from cur.
    int index = 0;
    for (int child : graph[cur]) // include one edge from cur.
    {
        if (child == parent)
            continue;
        currentSum = max(currentSum, 1 + sumOfChildren - temp[index].second + temp[index].first);
        index++;
    }
    // cout << cur << " " << parent << " " << sumOfChildren << " " << currentSum << endl;
    ans = max(ans, currentSum);
    return {sumOfChildren, currentSum};
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1, vector<int>());

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int ans = 0;
    dfs(graph, 1, 0, ans);
    cout << ans << "\n";
    return 0;
}