#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * SINGLE SOURCE "K" SHORTEST PATH (including cycle)
 *
 * Top K routes from 1 -> N
 *
 * Not DAG!! Unique Route INCLUDING cycle!
 * A route can visit the same city several times. => Can use the same edge multiple times
 *
 * Should aim to get top K route. If we want to get all route, -> will lead to inf loop since there could be a cycle!
 *
 * 1) DFS? -> Since graph has a cycle backTrack will go infinite
 * 2) Bellman Ford? -> How to tell the redundant paths? Also path with cycle.. how?
 */

struct Edge
{
  int to;
  int cost;
};

struct Route
{
  int to;
  unsigned long cost;
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  const unsigned long MAX_COST = 3e14;

  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<Edge>> graph(n + 1);
  vector<priority_queue<unsigned long>> topKdists(n + 1); // Store smallest K routes, MAX HEAP
  topKdists[1].push(0);

  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
  }

  auto comp = [](const Route &a, const Route &b)
  { return a.cost > b.cost; };
  priority_queue<Route, vector<Route>, decltype(comp)> pq(comp); // min Heap
  pq.push({1, 0});

  while (!pq.empty())
  {
    Route r = pq.top();
    pq.pop();

    // cout << r.cost << " ";

    if (r.cost > topKdists[r.to].top()) // can't break into top k distance
    {
      continue;
    }
    // continue;
    for (Edge &e : graph[r.to]) // (1 + E/V)
    {
      unsigned long newDist = r.cost + e.cost; // new distance from 1 -> r.to -> e.to

      if (topKdists[e.to].size() < k || topKdists[e.to].top() > newDist) // better than the worst case
      {
        topKdists[e.to].push(newDist); // KlogK
        if (topKdists[e.to].size() > k)
        {
          topKdists[e.to].pop();
        }
        pq.push({e.to, newDist});
      }
    }
  }
  vector<unsigned long> v;
  while (!topKdists[n].empty()) // O(KlogK)
  {
    v.push_back(topKdists[n].top());
    // cout << topKdists[n].top() << " ";
    topKdists[n].pop();
  }
  for (auto iter = v.rbegin(); iter != v.rend(); ++iter)
  {
    cout << *iter << " ";
  }

  return 0;
}