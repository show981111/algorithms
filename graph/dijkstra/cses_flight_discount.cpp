#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Dijkstra + DP
 *
 * T(Node, #discount) = Min cost to get to the Node from Src using at most #discout
 *
 * T(Node, 0) = min(T(neighbor of Node,0) + Cost[neighbor -> Node]);
 * T(Node, 1) = min(T(neighbor of Node,0) + Cost[neighbor -> Node]/2, T(neighbor of Node,1) + Cost[neighbor -> Node])
 *                  // Discount apply now                             // Discount applied previously
 */
const unsigned long MAX_COST = 1e14;

struct Tix
{
    int to;
    int cost;
};
struct Route
{
    int to;
    unsigned long totalCost;
    bool discountUsed;
};
struct MinCost
{
    unsigned long zeroDiscount = MAX_COST;
    unsigned long oneDiscount = MAX_COST;
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<Tix>> graph(n + 1);
    vector<MinCost> costs(n + 1);
    costs[1].oneDiscount = 0;
    costs[1].zeroDiscount = 0;

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    auto comp = [](const Route &a, const Route &b)
    {
        return a.totalCost > b.totalCost;
    };
    priority_queue<Route, vector<Route>, decltype(comp)> pq(comp);
    pq.push({1, 0});

    while (!pq.empty())
    {
        Route cur = pq.top();
        pq.pop();

        if (cur.discountUsed && min(costs[cur.to].oneDiscount, costs[cur.to].zeroDiscount) < cur.totalCost)
        {
            continue;
        }
        if (!cur.discountUsed && costs[cur.to].zeroDiscount < cur.totalCost)
        {
            continue;
        }

        for (Tix &neighbor : graph[cur.to])
        {
            unsigned long newCostWithoutCurDiscount = cur.totalCost + neighbor.cost;
            unsigned long newCostWithCurDiscount = cur.totalCost + neighbor.cost / 2;
            if (!cur.discountUsed)
            {
                if (costs[neighbor.to].zeroDiscount > newCostWithoutCurDiscount)
                {
                    costs[neighbor.to].zeroDiscount = newCostWithoutCurDiscount;
                    pq.push({neighbor.to, newCostWithoutCurDiscount, false});
                }
                if (costs[neighbor.to].oneDiscount > newCostWithCurDiscount)
                {
                    costs[neighbor.to].oneDiscount = newCostWithCurDiscount;
                    pq.push({neighbor.to, newCostWithCurDiscount, true});
                }
            }
            else
            { // already used discount -> can't update zero discount
                if (costs[neighbor.to].oneDiscount > newCostWithoutCurDiscount)
                {
                    costs[neighbor.to].oneDiscount = newCostWithoutCurDiscount;
                    pq.push({neighbor.to, newCostWithoutCurDiscount, true});
                }
            }
        }
    }
    cout << costs[n].oneDiscount;
    return 0;
}