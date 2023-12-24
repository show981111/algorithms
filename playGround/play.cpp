#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * CYCLE FOUND IN DIRECTED/UNDIRECTED GRAPH
 *
 * Use DFS -> O(E) solution!
 * Use node coloring: 3 states = Unvisited, visited, Instack
 *
 * We do not have to set visited node to unvisited to backtrack because
 * if we go into cycle once, we will def get a cycle.
 * If we confirmed that path does not make a cycle, we can conclude none of nodes in that path creates a cycle.
 *
 */
typedef vector<vector<int>> Graph;
enum STATE
{
  UNVISITED,
  VISITED,
  INSTACK
};
// put initial starting point to stack
void dfs(Graph &graph, int cur, vector<STATE> &status, vector<int> &cycle, bool &cycleFound, bool &isPartOfCycle)
{
  for (int neighbor : graph[cur])
  {
    if (status[neighbor] == UNVISITED)
    {
      status[neighbor] = INSTACK;
      dfs(graph, neighbor, status, cycle, cycleFound, isPartOfCycle);
    }
    else if (status[neighbor] == INSTACK)
    {
      // cycle found
      cycleFound = true;
      cycle.push_back(neighbor); // neighbor is the cycle starting point
      cycle.push_back(cur);      // inner cycle starts
      isPartOfCycle = true;
      return;
    }
    // VISITED, just skip

    if (cycleFound)
    {
      if (isPartOfCycle)
      {
        cycle.push_back(cur);
        if (cur == cycle[0])
          isPartOfCycle = false; // came back to the beginning of the cycle
      }
      return;
    }
  }
  status[cur] = VISITED;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<int> v;
  Graph graph(n + 1);
  vector<STATE> status(n + 1, UNVISITED);
  vector<int> cycle;
  for (int i = 0; i < m; i++)
  {
    int from, to;
    cin >> from >> to;
    graph[from].push_back(to);
  }
  bool cycleFound = false, isPartOfCycle = false;
  for (int i = 1; i <= n; i++)
  {
    if (status[i] == VISITED)
      continue;

    status[i] = INSTACK;
    dfs(graph, i, status, cycle, cycleFound, isPartOfCycle);

    if (cycleFound)
    {
      cout << cycle.size() << "\n";
      for (int i = cycle.size() - 1; i >= 0; i--)
        cout << cycle[i] << " ";
      return 0;
    }
  }

  cout << "IMPOSSIBLE\n";

  return 0;
}