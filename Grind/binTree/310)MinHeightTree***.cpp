/**
 * @brief Getting the root of minimum height tree (Diameter of tree)
 *
 * The root of min heigh tree is the "mid point" of Diameter(longest path)
 * A) Topological Sort -> start from indegree == 1 (since undirected)
 * B) DFS/BFS
 */

// Top Sort
class Solution
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if (edges.empty())
            return {0};
        vector<int> ans;
        vector<vector<int>> adj(n);
        vector<int> indegrees(n, 0);
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            indegrees[e[0]]++;
            indegrees[e[1]]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (indegrees[i] == 1)
                q.push(i);
        }
        int qSize;
        vector<int> path;
        int length = 0;
        while (!q.empty())
        {
            qSize = q.size();
            length++;
            for (int i = 0; i < qSize; i++)
            {
                int cur = q.front();
                q.pop();
                path.push_back(cur);
                for (auto neighbor : adj[cur])
                {
                    if (--indegrees[neighbor] == 1)
                    {
                        q.push(neighbor);
                    }
                }
            }
        }
        length = 2 * (length - 1);
        ans.push_back(path.back());

        if (qSize == 2)
        {
            ans.push_back(path[path.size() - 2]);
            length++;
        }
        cout << length << endl;
        return ans;
    }
};

// DFS/ BFS
class Solution
{
public:
    // int dfs(int start, vector<vector<int>> &adj, vector<int> &path){
    //     path.push_back(start);
    // }

    int bfs(int start, vector<vector<int>> &adj, vector<int> &prev, int &dis)
    {
        queue<int> q;
        q.push(start);
        int last;

        while (!q.empty())
        {
            int qSize = q.size();
            dis++;
            for (int s = 0; s < qSize; s++)
            {
                last = q.front();
                q.pop();
                for (int i = 0; i < adj[last].size(); i++)
                {
                    if (prev[last] != adj[last][i])
                    {
                        q.push(adj[last][i]);
                        prev[adj[last][i]] = last;
                    }
                }
            }
        }
        return last;
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if (edges.empty())
            return {0};
        // if(edges.size() == 0)
        //     return edges[0];
        vector<vector<int>> adj(n);
        vector<int> prev(n, -1);
        vector<int> ans;
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        int dis = 0;
        int oneEnd = bfs(0, adj, prev, dis);
        fill(prev.begin(), prev.end(), -1);
        dis = 0;
        int otherEnd = bfs(oneEnd, adj, prev, dis);

        int cur = otherEnd, behind = cur;
        int iter = dis / 2;
        // cout << dis << endl;
        while (iter > 0)
        {
            behind = cur;
            cur = prev[cur];
            iter--;
        }
        ans.push_back(cur);
        if (dis % 2 == 0)
        {
            ans.push_back(behind);
        }
        return ans;
    }
};