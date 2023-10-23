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
 * https://cses.fi/problemset/task/1672
 *
 *
 * Floyd–Warshall algorithm
 * Shortest distance from all nodes to all other noces. (O(N^3))
 *
 * Initialize distance matrix, and use the fact that dist(x,y) = dist(x,c) + dist(c,y)
 *
 * For all possible "c", we update the distance of all possible pairs of nodes (x,y)
 * So it is like DP.
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
  const long NegInf = -1e13;

  int n, m;
  cin >> n >> m;
  vector<long> distance(n + 1, NegInf);
  vector<bool> reachableFromN_reverse(n + 1, false);
  vector<Edge> edges;
  reachableFromN_reverse[n] = true;
  for (int i = 0; i < m; i++)
  {
    int a, b, x;
    cin >> a >> b >> x;
    edges.push_back(Edge{a, b, x});
    if (a == 1)
    {
      distance[b] = x;
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
      if (distance[e.src] != NegInf && distance[e.src] + e.weight > distance[e.dest])
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
    cout << distance[n];

  return 0;
}