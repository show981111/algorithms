class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        vector<int> dist(n + 1, INT_MAX);
        vector<vector<pair<int, int>>> graph(n + 1); // node, times
        for (auto &v : times)
            graph[v[0]].push_back({v[1], v[2]});

        queue<int> q;
        dist[k] = 0;
        q.push(k);

        while (!q.empty())
        {
            int f = q.front();
            q.pop();
            for (auto &next : graph[f])
            {
                if (dist[next.first] > dist[f] + next.second)
                {
                    dist[next.first] = dist[f] + next.second;
                    q.push(next.first);
                }
            }
        }

        int ans = dist[k];
        for (int i = 1; i < n + 1; i++)
            ans = max(dist[i], ans);
        return ans == INT_MAX ? -1 : ans;
    }
};