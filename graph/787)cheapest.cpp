/**
 * @brief TLE
 *
 */
class Solution
{
public:
    struct Edge
    {
        int to;
        int cost;
        Edge(int t, int c) : to(t), cost(c) {}
    };
    void dfs(vector<vector<Edge>> &graph, vector<bool> &visited, int dst, int k, int start, int stops, int cost, int &minCost)
    {
        // cout << start << cost << endl;
        if (start == dst && stops <= k + 1)
        {
            minCost = min(minCost, cost);
            return;
        }
        visited[start] = true;
        if (stops <= k)
        {
            for (int i = 0; i < graph[start].size(); i++)
            {
                int next = graph[start][i].to;
                if (!visited[next] && cost + graph[start][i].cost < minCost)
                {
                    dfs(graph, visited, dst, k, next, stops + 1, cost + graph[start][i].cost, minCost);
                }
            }
        }
        visited[start] = false;
    }
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        int ans = INT_MAX;
        vector<vector<Edge>> graph(n);
        for (auto &f : flights)
        {
            graph[f[0]].push_back(Edge(f[1], f[2]));
        }
        vector<bool> visited(n, false);
        dfs(graph, visited, dst, k, src, 0, 0, ans);
        return ans == INT_MAX ? -1 : ans;
    }
};