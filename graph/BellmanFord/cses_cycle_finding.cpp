#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * Cycle Finding
 * <2> trial -> BELLMAN FORD?
 * Need to do it from every vertex, since cycle might not be reachable from a single source
 * => [TRICK] To prevent this, insert a node "0" and connect 0 with all other nodes with 0 weight!! Then perfom Bellman Ford from node "0"!
 *            If there is a negative cycle, the distance will go negative!!
 *
 * How to get an actual cycle from Bellman Ford?
 *
 * 1. At N_th iteration, let's say we got additonal relax and we know that there is a negative cycle.
 *    The key of Bellman ford is that this relax will give us an edge that is **REACHABLE** from the negative cycle!
 *       The reason is that, since negative cycle reduces distance[e.from], when we do relax, even though the edge "e" is not in the cycle,
 *        We have distance[e.from] + e.weight < distance[e.to]
 *
 * So NOW we have an edge that is reachable from negative cycle.
 * How can we get an actual cycle??
 *
 * 2. Use a parent array. We trace back parent "enough time (N-1)" then we can reach to the element in the cycle.
 *      Why? Since there are N nodes, there could be maximum N-1 edges in between. Also, as soon as we get into the cycle,
 *      the parent array will circle.
 *      EX) 1 -> 2 -> 3 -> 1
 *                      -> [4] : edge that got relaxed again. As we step into the parent of 3, the parent array is circling wihtin the cycle
 *      Node   1 2 3 4
 *      PARENT 3 1 2 3
 *
 * Actually, if we use a parent array, we can get the actual shrotest path too!
 * https://www.youtube.com/watch?v=kZfm68XKC58&ab_channel=Dardev
 */

struct Edge
{
    int from;
    int to;
    int weight;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    vector<long> dists(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.push_back({from, to, weight});
    }
    for (int i = 1; i <= n; i++)
    {
        edges.push_back({0, i, 0}); // connect every graph with 0
    }

    vector<int> cycle;
    int till = -1;
    vector<int> parents(n + 1);

    for (int i = 0; i <= n; i++)
    {
        for (Edge &e : edges)
        {
            long newDistanceToReachTo = dists[e.from] + e.weight;
            if (dists[e.to] > newDistanceToReachTo)
            {
                dists[e.to] = newDistanceToReachTo;
                parents[e.to] = e.from;
                if (i == n)
                {                // there is a negative cycle!
                    till = e.to; // edges that got reduced additionally due to negative cycle that happened at least before!!
                    // cout << "Cycle Found " << e.from << " " << e.to << "\n";
                    break;
                }
            }
        }
    }

    if (till != -1)
    {
        for (int i = 0; i < n; i++)
            till = parents[till]; // Trace back to the actual cycle elements
        // cout << "Cycle starts " << cycleStarts << endl;
        // cycle.push_back(cycleStarts);
        int node = till;
        while (node != till || cycle.empty())
        {
            cycle.push_back(node);
            node = parents[node];
            // cout << node << " ";
        }
        cycle.push_back(till); // cycle end at the same node as it started
        cout << "YES\n";
        for (int i = cycle.size() - 1; i >= 0; i--)
        {
            cout << cycle[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "NO\n";
    }
    return 0;
}