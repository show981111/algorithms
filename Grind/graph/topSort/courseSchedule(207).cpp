/**
 * @brief DFS / BFS Cycle Detection
 * DFS: DFS finds the path from X to Y.
 * Thus, we only need to check when we are finding a path from X to Y,
 * is that node is visited again? -> cycle.
 *
 * Below dfs, cStack saves nodes that are in the current call stack(current path)
 * so if the node is already in call stack and revisited? -> cyclic
 */

class Solution
{
public:
    bool dfs(vector<bool> &visited, vector<vector<int>> &graph, int x, vector<bool> &cStack)
    {
        visited[x] = true;
        cStack[x] = true;
        bool res;
        for (auto &next : graph[x])
        {
            if (cStack[next])
                return false;
            if (!visited[next])
            {
                res = dfs(visited, graph, next, cStack);
                if (res == false)
                    return false;
            }
        }
        cStack[x] = false;
        return true;
    }
    /**
     * @brief Different DFS
     * Only use one container, visited[x] = 1, visited for firstime, x is in the current paht
     * visited[x] = 0, not visited
     * visited[x] = 2, visited node, but not in the current path(confirmed as a non cyclic).
     *
     */
    bool dfs(vector<int> &visited, vector<vector<int>> &graph, int x)
    {
        visited[x] = 1;
        bool res;
        for (auto &next : graph[x])
        {
            if (visited[next] == 1)
                return false;
            if (visited[next] == 0)
            {
                res = dfs(visited, graph, next);
                if (res == false)
                    return false;
            }
        }
        visited[x] = 2;
        return true;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<bool> visited(numCourses, false);
        vector<bool> callStack(numCourses, false);
        vector<vector<int>> graph(numCourses);
        for (auto &pair : prerequisites)
        {
            graph[pair[1]].push_back(pair[0]);
        }
        for (int i = 0; i < numCourses; i++)
        {
            if (!visited[i])
            {
                bool res = dfs(visited, graph, i, callStack);
                if (res == false)
                    return false;
            }
        }

        return true;
    }
};

/**
 * @brief BFS topological sort
 *  if there is a cycle, then those nodes cannot be sorted because
 * indegree cannot be a zero for nodes in cycle.
 */

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> graph(numCourses);
        for (auto &pair : prerequisites)
        {
            graph[pair[1]].push_back(pair[0]);
            indegree[pair[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
        int sorted = 0;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            sorted++;
            for (int next : graph[cur])
            {
                if (--indegree[next] == 0)
                    q.push(next);
            }
        }

        return sorted == numCourses;
    }
};