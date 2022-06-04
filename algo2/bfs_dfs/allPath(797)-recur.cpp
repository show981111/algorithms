class Solution
{
public:
    vector<vector<int>> res;
    vector<bool> visited;
    int dest;
    vector<int> path;

    void dfs(vector<vector<int>> &graph, int cur)
    {
        visited[cur] = true;

        if (cur == dest)
        {
            res.push_back(path);
        }
        for (int i = 0; i < graph[cur].size(); i++)
        {
            if (visited[graph[cur][i]] == false)
            {
                path.push_back(graph[cur][i]);
                dfs(graph, graph[cur][i]);
                path.pop_back();
            }
        }
        visited[cur] = false;
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        dest = graph.size() - 1;
        visited.resize(dest + 1, false);
        path.reserve(dest + 1);
        path.push_back(0);

        dfs(graph, 0);

        return res;
    }
};