#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * Top K routes from 1 -> N
 *
 * 1) DFS brute force O(V^V) due to backtrack
 * 2) Bellman Ford?
 */

struct Edge
{
    int from;
    int to;
    int cost;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    const unsigned long MAX_COST = 3e14;

    int n, m, k;
    cin >> n >> m >> k;

    vector<Edge> edges;
    vector<unsigned long> dists(n + 1, MAX_COST);
    dists[1] = 0;
    vector<unsigned long> costToTarget;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (Edge &e : edges)
        {
            if (dists[e.from] != MAX_COST)
            {
                unsigned long newCost = dists[e.from] + e.cost;
                if (e.to == n)
                    costToTarget.push_back(newCost);
                if (dists[e.to] > newCost)
                {
                    dists[e.to] = newCost;
                }
            }
        }
    }
    sort(costToTarget.begin(), costToTarget.end());

    for (int i = 0; i < k; i++)
        cout << costToTarget[i] << " ";

    return 0;
}