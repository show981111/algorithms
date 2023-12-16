#include <iostream>
#include <vector>

using namespace std;

const unsigned long MAX_COST = 1e14;

/**
 * Using Bellman-Ford => DP on #edges we are using
 *
 * Single Source shortest/longest
 *
 * T(to, cnt) = min cost to go from single source -> to using #cnt edges
 * For cnt in Total number of edgs:
 *    For edge in Edges:
 *       T(edge.to, cnt) = min(T(edge.to, cnt), T(edge.from, cnt -1) + edge.weight)
 *
 * Additional condition:
 *  We can use the discount coupon once which makes the edge wight half!
 *
 * Now, dp is
 * T(to, cnt, ZERO/ONE DISCOUNT) = min cost to go from single source -> using #cnt edges with ONE/ZERO discount
 *
 * T(edge.to, cnt, ZERO DISCOUNT) = min(T(edge.to, cnt, ZERO DISCOUNT), T(edge.from, cnt -1, ZERO DISCOUNT) + edge.weight)
 * T(edge.to, cnt, ONE DISCOUNT) = min(T(edge.to, cnt, ONE DISCOUNT), T(edge.from, cnt -1, ZERO DISCOUNT) + edge.weight/2, -> Discount on current edge
 *                                     T(edge.from, cnt -1, ONE DISCOUNT) + edge.weight); -> Discount on previous edges we visited.
 *
 * TC: O(VE)
 */
struct Edge
{
    int from;
    int to;
    int price;
};

struct Cost
{
    unsigned long zeroDiscountCost = MAX_COST;
    unsigned long oneDiscountCost = MAX_COST;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Cost> dp(n + 1);
    dp[1].zeroDiscountCost = 0;
    dp[1].oneDiscountCost = 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i)
    {
        int from, to, price;
        cin >> from >> to >> price;
        edges[i] = Edge{from, to, price};
    }

    for (int edgeCnt = 0; edgeCnt < m; ++edgeCnt)
    {
        for (const Edge &e : edges)
        {
            unsigned long newCostWithNoDiscount = dp[e.from].zeroDiscountCost + e.price;
            unsigned long newCostWithCurrentDiscount = dp[e.from].zeroDiscountCost + e.price / 2;
            unsigned long newCostWithPreviousDiscount = dp[e.from].oneDiscountCost + e.price;

            dp[e.to].zeroDiscountCost = min(dp[e.to].zeroDiscountCost, newCostWithNoDiscount);
            dp[e.to].oneDiscountCost = min(dp[e.to].oneDiscountCost, min(newCostWithCurrentDiscount, newCostWithPreviousDiscount));
        }
    }

    cout << min(dp[n].oneDiscountCost, dp[n].zeroDiscountCost);
    return 0;
}
