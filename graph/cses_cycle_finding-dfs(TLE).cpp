#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * Cycle Finding - Using DFS
 * If we visited the node that is already in the stack -> CYCLE!
 *
 * How to specfically get the cycle?
 * Unwind the stack until we see the start point of the cycle
 * EX) 0 -> 1 -> (2 -> 3 -> 4 -> 5 -> 2)
 *             | unwind until here. Should not include 0 & 1
 *
 * Is backtrack necessary?
 *  -> If we only need to find any cycle it is not necessary.
 *     Because as soon as we step into cycle, we will get a cycle no matter what
 * BackTrack is necessary because we only need a negative cycle.
 */

struct Edge
{
    int dest;
    int weight;
};

void dfs(vector<vector<Edge>> &graph, int cur, unordered_map<int, long> &nodeToWeight,
         vector<bool> &visited, vector<int> &cycle, bool &cycleFound, bool &isPartOfCycle)
{
    visited[cur] = true; // As a group
    // cout << "Cur " << cur << " : ";
    for (Edge &neighbor : graph[cur])
    {
        long curWeight = nodeToWeight[cur] + neighbor.weight;
        if (nodeToWeight.count(neighbor.dest) > 0)
        {
            // we already visited this destination on the way
            long cycleWeight = curWeight - nodeToWeight[neighbor.dest];
            // cout << neighbor.dest << " -> " << cycleWeight << "\n";
            if (cycleWeight < 0)
            {
                cycleFound = true;
                cycle.push_back(neighbor.dest);
                cycle.push_back(cur);
                isPartOfCycle = true;
                // cout << "Cycle detected " << neighbor.dest << "\n";
                return;
            }
        }
        else
        {
            nodeToWeight[neighbor.dest] = curWeight;
            dfs(graph, neighbor.dest, nodeToWeight, visited, cycle, cycleFound, isPartOfCycle);

            if (cycleFound)
            {
                // cout << "Cycle FOund cur = " << cur << endl;
                if (isPartOfCycle)
                    cycle.push_back(cur);
                if (cur == cycle[0]) // Came to the cycle starting point
                    isPartOfCycle = false;
                return;
            }
        }
    }

    nodeToWeight.erase(cur);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    vector<bool> visited(n + 1, false);
    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
    }

    vector<int> cycle;
    bool cycleFound = false;
    for (int i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;

        unordered_map<int, long> nodeToWeight;
        nodeToWeight[i] = 0;
        bool isPartOfCycle = false;
        dfs(graph, i, nodeToWeight, visited, cycle, cycleFound, isPartOfCycle);
        // cout << "Cycle Found? " << cycleFound << "\n";

        if (cycleFound)
            break;
    }

    if (cycleFound)
    {
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