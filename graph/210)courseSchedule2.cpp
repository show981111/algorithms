/**
 * @brief Topological Sort
 *
 * 1) DFS
 *
 * 2) BFS
 *
 */

class Solution
{
public:
    bool dfsTopSort(vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &trace, vector<int> &result, int cur)
    {
        if (visited[cur])
            return true;
        visited[cur] = true;
        trace[cur] = true;

        for (int neighbor : graph[cur])
        {
            if (trace[neighbor])
            {
                return false;
            }
            bool res = dfsTopSort(graph, visited, trace, result, neighbor);
            if (!res)
                return res;
        }
        trace[cur] = false;
        result.push_back(cur);
        return true;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> graph(numCourses);
        for (auto &edge : prerequisites)
        {
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(numCourses);
        vector<int> result;

        for (int i = 0; i < numCourses; i++)
        {
            vector<bool> trace(numCourses, false);
            bool res = dfsTopSort(graph, visited, trace, result, i);
            if (!res)
                return vector<int>();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

/**
 * @brief BFS
 * Using an InDegree, if the result == #total nodes -> good,
 * unless, cycles exists
 */

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> graph(numCourses);
        vector<int> inEdges(numCourses, 0);
        for (auto &edge : prerequisites)
        {
            graph[edge[1]].push_back(edge[0]);
            inEdges[edge[0]]++;
        }
        queue<int> q;
        vector<bool> visited(numCourses, false);

        for (int i = 0; i < inEdges.size(); i++)
        {
            if (inEdges[i] == 0)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        vector<int> res;
        while (!q.empty())
        {
            int node = q.front();
            res.push_back(node);
            q.pop();
            for (int neighbor : graph[node])
            {
                inEdges[neighbor]--;
                if (!visited[neighbor] && inEdges[neighbor] == 0)
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        if (res.size() != numCourses)
            return vector<int>();
        return res;
    }
};