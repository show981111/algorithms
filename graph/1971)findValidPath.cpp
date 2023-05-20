/**
 * @brief Classic DFS/BFS
 *
 * Check the format of "edges" or "graph"!!
 * Is it just the set of edges, or index -> to graph?
 *
 * Where should we check visited?
 * DFS: Doesn't matter but before we call another dfs
 * BFS: before we go to next iteration! => If it shares the parent, then it can be inserted twice
 *      RULE is, "A node should be inserted only once to the Queue!"
 */

class Solution
{
public:
    bool dfs(vector<vector<int>> &edges, vector<bool> &visited, int cur, int dest)
    {
        if (cur == dest)
        {
            return true;
        }
        // Or we can put visited[src] = true here!
        for (int neighbor : edges[cur])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                bool res = dfs(edges, visited, neighbor, dest);
                if (res)
                    return res;
            }
        }
        return false;
    }
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<bool> visited(n, false);
        vector<vector<int>> graph(n);
        for (vector<int> &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        visited[source] = true;
        // mark sources as visited => allow us to put visited at line 23
        // Unless, it will visit the source again!
        return dfs(graph, visited, source, destination);
    }
};

/*
BFS
*/

class Solution
{
public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<bool> visited(n, false);
        vector<vector<int>> graph(n);
        for (vector<int> &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        queue<int> q;
        q.push(source);
        visited[source] = true;
        while (!q.empty())
        {
            int f = q.front();
            q.pop();
            if (f == destination)
                return true;

            for (int to : graph[f])
            {
                if (!visited[to])
                {
                    visited[to] = true; // mark visited here! -> prevent inserting the same node twice to the queue!
                    q.push(to);
                }
            }
        }
        return false;
    }
};