#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * https://codeforces.com/group/62c8bIEN9G/contest/473781/status/E
 */
struct Loc
{
    int aLoc = -1;
    int bLoc = -1;
};

Loc getLCA(const vector<vector<int>> &graph, int cur, int a, int b, int &lca)
{
    if (cur == a)
        return {cur, -1};
    if (cur == b)
        return {-1, cur};

    Loc res;
    for (int child : graph[cur])
    {
        Loc c = getLCA(graph, child, a, b, lca);
        if (c.aLoc != -1)
            res.aLoc = c.aLoc;
        if (c.bLoc != -1)
            res.bLoc = c.bLoc;
    }
    // cout << "CUR " << cur << " " << res.aLoc << " " << res.bLoc << endl;
    if (res.aLoc != -1 && res.bLoc != -1 && lca == -1)
    {
        lca = cur;
    }

    return res;
}
unsigned long calMinCostForTwoLeaf(const vector<vector<int>> &graph, const vector<int> &roots, const vector<unsigned long> &minCost, int a, int b)
{
    int lca = -1;
    for (int i = 0; i < roots.size(); i++)
    {
        getLCA(graph, roots[i], a, b, lca);
        // cout << a << " " << b << " from " << i << " " << lca << endl;
        if (lca != -1)
            break;
    }
    // cout << "LCA of " << a << " " << b << " " << lca << endl;
    if (lca != -1)
    {

        return min(minCost[a] + minCost[b] - minCost[lca], minCost[a] + minCost[b]);
    }
    else
    {
        return minCost[a] + minCost[b];
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    // cout << n << " " << m << endl;

    vector<int> pages(n, 0);
    vector<vector<int>> graph(n);
    vector<unsigned long> minCost(n, INT_MAX);
    vector<int> ind(n, 0);
    vector<int> leafs;
    vector<int> roots;

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }
    for (int i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        ind[to - 1]++;
    }

    for (int i = 0; i < n; i++)
    {
        if (ind[i] == 0)
        {
            q.push(i);
            roots.push_back(i);
            minCost[i] = pages[i];
        }
        if (graph[i].size() == 0)
        {
            leafs.push_back(i);
        }
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int child : graph[cur])
        {
            minCost[child] = min(minCost[child], minCost[cur] + pages[child]);
            ind[child]--;
            if (ind[child] == 0)
            {
                q.push(child);
            }
        }
    }
    unsigned long ans = 0;
    for (int i = 0; i < leafs.size(); i++)
    {
        for (int j = i + 1; j < leafs.size(); j++)
        {
            unsigned long val = calMinCostForTwoLeaf(graph, roots, minCost, leafs[i], leafs[j]);
            if (ans == 0)
                ans = val;
            else
                ans = min(ans, val);
        }
    }
    // for (int i = 0; i < minCost.size(); i++)
    // {
    //     cout << minCost[i] << " ";
    // }
    // cout << endl;
    cout << ans << "\n";
    return 0;
}