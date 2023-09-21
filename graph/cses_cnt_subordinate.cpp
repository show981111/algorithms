#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * Counting the number of all descendants!
 *
 * Do dfs, return the size of subtree from dfs!
 * record answer in cnt array!
 */

int dfs(vector<vector<int>> &graph, vector<int> &cnt, int cur)
{
    int sum = 0;
    for (int child : graph[cur])
    {
        sum += dfs(graph, cnt, child);
    }

    // if (graph[cur].size() == 0)
    // { // leaf node
    //     return 1; same as sum + 1 for leaf node
    // }
    cnt[cur] = sum;
    return sum + 1;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<int> cnt(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int parent;
        cin >> parent;
        graph[parent].push_back(i);
    }

    dfs(graph, cnt, 1);

    for (int i = 1; i <= n; i++)
        cout << cnt[i] << " ";

    return 0;
}