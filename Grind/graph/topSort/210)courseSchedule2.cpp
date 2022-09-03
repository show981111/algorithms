/**
 * @brief TOPSORT USING DFS
 *
 * Cycle detection using visitedNode(By checking if it revisit the nodes in the path)
 * + stacking nodes for topSort.
 * We should Add elements in Stack when we return DFS.(popping from the callStack)
 * because it means we traversed all of its children!
 *
 * It does not matter to pick which node to start
 * because We will put all children of current node to stack.
 * After then, it will be ancestors of this node!
 * So it does not matter which node we start with!
 */

class Solution
{
public:
    bool dfs(vector<vector<int>> &graph, vector<int> &visited, stack<int> &topSort, int start)
    {
        visited[start] = 1;

        for (int i = 0; i < graph[start].size(); i++)
        {
            int next = graph[start][i];
            if (visited[next] == 0)
            {
                visited[next] = true;
                bool res = dfs(graph, visited, topSort, next);
                if (!res)
                    return false;
            }
            else if (visited[next] == 1)
            {
                return false;
            }
        }

        topSort.push(start);
        visited[start] = 2;
        return true;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> graph(numCourses);
        for (auto &v : prerequisites)
        {
            graph[v[1]].push_back(v[0]);
        }

        stack<int> topSort;
        vector<int> visited(numCourses, 0);
        vector<int> ans;

        for (int i = 0; i < numCourses; i++)
        {
            if (visited[i] == 0)
            {
                bool res = dfs(graph, visited, topSort, i);
                if (!res)
                    return ans;
            }
        }

        while (!topSort.empty())
        {
            ans.push_back(topSort.top());
            topSort.pop();
        }
        return ans;
    }
};