#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <limits>

using namespace std;

/**
 * https://cses.fi/problemset/task/1671
 *
 * Dijkstra - Greedy
 *
 * Want to know the shortest distance from A to all other nodes.
 * At each moment, greedily select the node that is closest.
 * Then from that closest node(from source), update the distance to reach the neighbor of that selected node.
 *
 * Dijkstra's assumption is that when we pop the node, it is impossible to get a better distance to that node (Say it is processed).
 * We are processing the nodes that are **closest from the source**.
 *
 * Dist(A,B) can't have a shorter route when it is popped from the PQ.
 * Why? that means, there exists a C such tat Dist(A,C) + Dist(C,B) < current Dist(A,B)
 * Then, Dist(A,C) shouldve inserted to PQ cuz it is shorter route from the source(A)
 * and Dist(C,B) shouldve inserted to PQ since Dist(A,C) is shorter, which means Dist(A,C) shouldve processed first.
 * Then since Dist(A,C) & Dist(C,B) < current Dist(A,B), which means Dist(A->C->B) < current Dist(A,B), and it is impossible
 * to get current Dist(A,B) before Dist(A->C->B) since we are popping the shortest distance from the SOURCE
 *
 */
struct To
{
    int dest;
    unsigned long length;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<To>> graph(n + 1);
    vector<unsigned long> dist(n + 1, numeric_limits<unsigned long>::max());
    dist[1] = 0;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(To{b, (unsigned long)c});
    }
    auto comp = [](const To &a, const To &b)
    { return a.length > b.length; };
    priority_queue<To, vector<To>, decltype(comp)> pq(comp);
    pq.push({1, 0});

    while (!pq.empty())
    {
        To t = pq.top();
        pq.pop();

        if (dist[t.dest] < t.length) // Optimization cant put <=, cuz that will skip the correct one too!
            continue;

        for (To &neighbor : graph[t.dest])
        {
            if (dist[neighbor.dest] > dist[t.dest] + neighbor.length)
            {
                dist[neighbor.dest] = dist[t.dest] + neighbor.length;
                neighbor.length = dist[neighbor.dest];
                pq.push(neighbor);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }

    return 0;
}