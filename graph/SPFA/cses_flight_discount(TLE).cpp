#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const unsigned long MAX_COST = 1e14;

/**
 * Use BFS instead of Two loops in Bellman Ford.
 *
 * In Queue, Node is stored.
 *
 * q.push(source);
 * updated distance_to[source] = 0;
 *
 * While(!q.empty())
 *    node v = q.front(); q.pop();
 *    for(neighbor : graph[v]) // find v's neighbor
 *       NewDist = dp[v] + v->neighbor weight // going throguh v to get to neighbor
 *       if(NewDist < dp[neighbor])
 *             dp[neighbor] = NewDist;
 *             If neighbor not in q: // If neighbor is already in Queue, u can just update the distances when you pop that node.
 *                                   // Since we are grabbing the distance information from dp so it doesn't matter
 *                  q.push({neighbor});
 */

struct Trace
{
    int to;
    bool discountUsed;
};
struct Dest
{
    int to;
    int cost;
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
    vector<vector<Dest>> graph(n + 1);
    dp[1].zeroDiscountCost = 0;
    dp[1].oneDiscountCost = 0;

    for (int i = 0; i < m; ++i)
    {
        int from, to, price;
        cin >> from >> to >> price;
        graph[from].push_back({to, price});
    }

    queue<Trace> q;
    q.push({1, false});

    while (!q.empty())
    {
        Trace cur = q.front();
        q.pop();
        // distance from source to cur.to got optimized!

        for (const Dest &d : graph[cur.to]) // now optimized the distance from source -> cur.to -> cur.to's neighbor
        {
            // cout << d.to << " ";

            unsigned long newCostWithZeroDiscount = dp[cur.to].zeroDiscountCost + d.cost;
            unsigned long newCostWithCurrentDiscount = dp[cur.to].zeroDiscountCost + d.cost / 2;
            unsigned long newCostWithPrevDiscount = dp[cur.to].oneDiscountCost + d.cost;
            unsigned long minCostWithDiscount = min(newCostWithCurrentDiscount, newCostWithPrevDiscount);
            if (cur.discountUsed)
                minCostWithDiscount = newCostWithPrevDiscount;

            if (!cur.discountUsed && dp[d.to].zeroDiscountCost > newCostWithZeroDiscount)
            {
                dp[d.to].zeroDiscountCost = newCostWithZeroDiscount;
                q.push({d.to, false});
            }
            if (dp[d.to].oneDiscountCost > minCostWithDiscount)
            {
                dp[d.to].oneDiscountCost = minCostWithDiscount;
                q.push({d.to, true});
            }
        }
        // cout << endl;
    }

    cout << min(dp[n].oneDiscountCost, dp[n].zeroDiscountCost);
    return 0;
}

/**
 * A little better but still TLE.
 * Preventing redundant queuing by checking if its already in the queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

const unsigned long MAX_COST = 1e14;

struct Trace
{
    int to;
    bool discountUsed;
};
struct Dest
{
    int to;
    int cost;
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
    vector<vector<Dest>> graph(n + 1);
    dp[1].zeroDiscountCost = 0;
    dp[1].oneDiscountCost = 0;

    for (int i = 0; i < m; ++i)
    {
        int from, to, price;
        cin >> from >> to >> price;
        graph[from].push_back({to, price});
    }

    unordered_set<string> queued;

    queue<Trace> q;
    q.push({1, false});

    while (!q.empty())
    {
        Trace cur = q.front();
        q.pop();
        string setId = std::to_string(cur.to);
        if (cur.discountUsed)
            setId += "_1";
        else
            setId += "_0";
        queued.erase(setId);
        // distance from source to cur.to got optimized!

        for (const Dest &d : graph[cur.to]) // now optimized the distance from source -> cur.to -> cur.to's neighbor
        {
            // cout << d.to << " ";

            unsigned long newCostWithZeroDiscount = dp[cur.to].zeroDiscountCost + d.cost;
            unsigned long newCostWithCurrentDiscount = dp[cur.to].zeroDiscountCost + d.cost / 2;
            unsigned long newCostWithPrevDiscount = dp[cur.to].oneDiscountCost + d.cost;
            unsigned long minCostWithDiscount = min(newCostWithCurrentDiscount, newCostWithPrevDiscount);
            if (cur.discountUsed)
                minCostWithDiscount = newCostWithPrevDiscount;

            if (!cur.discountUsed && dp[d.to].zeroDiscountCost > newCostWithZeroDiscount)
            {
                dp[d.to].zeroDiscountCost = newCostWithZeroDiscount;
                string check = std::to_string(d.to) + "_0";
                if (queued.count(check) == 0) // Check if its queued or not.
                {
                    q.push({d.to, false});
                    queued.insert(check);
                }
            }
            if (dp[d.to].oneDiscountCost > minCostWithDiscount)
            {
                dp[d.to].oneDiscountCost = minCostWithDiscount;
                string check = std::to_string(d.to) + "_1";
                if (queued.count(check) == 0)
                {
                    q.push({d.to, true});
                    queued.insert(check);
                }
            }
        }
        // cout << endl;
    }

    cout << min(dp[n].oneDiscountCost, dp[n].zeroDiscountCost);
    return 0;
}
