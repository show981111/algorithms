/**
 * @brief
 * https://leetcode.com/problems/sum-of-distances-in-tree/solutions/1308366/c-solution-using-dfs-with-explanation-o-n-time-complexity/
 */
class Solution
{
public:
    // DistanceSum(cur) = SUM(distanceSum of each child) + SUM(size of each child subtree)
    void getOneDistanceSumDfs(vector<vector<int>> &graph, vector<int> &res, vector<int> &subtreeSize, int cur, int par)
    {
        int subtreeDistanceSum = 0;
        for (auto &child : graph[cur])
        {
            if (child != par)
            {
                getOneDistanceSumDfs(graph, res, subtreeSize, child, cur);
                subtreeDistanceSum += res[child];
                subtreeSize[cur] += subtreeSize[child] + 1; // child's subtree + child
            }
        }
        res[cur] += subtreeDistanceSum + subtreeSize[cur];
    }
    void getAllDistanceSumDfs(vector<vector<int>> &graph, vector<int> &res, vector<int> &subtreeSize, int cur, int par)
    {
        if (par != -1)
        {
            int n = graph.size();
            res[cur] = res[par] - (subtreeSize[cur] + 1) + (n - (subtreeSize[cur] + 1));
            // int fromParent = res[par] - (res[cur] + subtreeSize[cur] + 1) + n - (subtreeSize[cur] + 1);
            // res[cur] += fromParent; // res[cur] alr contain subtreesum!
        }
        for (auto &child : graph[cur])
        {
            if (child != par)
            {
                getAllDistanceSumDfs(graph, res, subtreeSize, child, cur);
            }
        }
    }
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> graph(n);
        for (auto &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        vector<int> res(n, 0);
        vector<int> subtreeSize(n, 0);
        getOneDistanceSumDfs(graph, res, subtreeSize, 0, -1);
        getAllDistanceSumDfs(graph, res, subtreeSize, 0, -1);
        return res;
    }
};