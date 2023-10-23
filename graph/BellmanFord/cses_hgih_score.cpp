#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
#include <unordered_set>
#include <limits>
#include <cassert>
using namespace std;

/**
 * https://cses.fi/problemset/task/1673/
 *
 *
 * Bellman Ford
 * Can be used to find the longest path in DAG.
 * As long as it does not have a positive cycle, it will converge.
 * If it has a positive cycle, the longest path can be infinity. Thus, it will fail.
 *
 * How do we find that there is a cycle?
 *
 * After N -1 round, in short at N_th cycle, if there is an edge that is still reduced,
 * that means using the same edge again gives an advantage => positive cycle.
 *
 * How can I tell if this cycle will affect the path Src -> Target?
 *
 * If the cycle is reachable from Src, and the Target is reachable from Target.
 * (1) Cycle is reachable from Src => If the final distance from Src to the cycle is not infinity, that node is reachable.
 * (2) Target is reachable from Cycle => This one, we do not know the all nodes that makes cycle. Thus, we cannot do if it is reachable from a single source.
 *                                       Also, at N-th round, it is possible that only one member of the cycle gets reduced, which makes us hard to identify who
 *                                       are the member of the cycle. Therefore, we use REVERSE graph. If, from target, we can reach any member of the cycle,
 *                                       that means cycle can reach the Target. Thus, from Target, check if any member of cycle is reachable
 * If both (1) and (2) are true, there is a cycle between src and target!
 */
struct Edge
{
    int src;
    int dest;
    int weight;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    const long INF = 1e13;

    int n, m;
    cin >> n >> m;
    vector<long> distance(n + 1, INF);
    vector<bool> reachableFromN_reverse(n + 1, false);
    vector<Edge> edges;
    reachableFromN_reverse[n] = true;
    for (int i = 0; i < m; i++)
    {
        int a, b, x;
        cin >> a >> b >> x;
        edges.push_back(Edge{a, b, -x});
        if (a == 1)
        {
            distance[b] = -x;
        }
        if (b == n)
        {
            reachableFromN_reverse[a] = true;
        }
    }
    distance[1] = 0;

    bool cycle = false;
    for (int i = 0; i < n; i++)
    {
        cycle = false;
        for (Edge &e : edges)
        {
            if (reachableFromN_reverse[e.dest])
            {
                // cout << e.dest << " is reachable " << e.src << " is also reachable\n";
                reachableFromN_reverse[e.src] = true;
            }
            if (distance[e.src] != INF && distance[e.src] + e.weight < distance[e.dest])
            {
                // cout << e.src << " is reachable, " << e.dest << " also \n";
                distance[e.dest] = distance[e.src] + e.weight;
                if (reachableFromN_reverse[e.dest] || reachableFromN_reverse[e.src])
                {
                    cycle = true;
                }
            }
        }
    }

    if (cycle)
        cout << -1;
    else
        cout << -distance[n];

    return 0;
}