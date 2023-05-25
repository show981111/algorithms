class Solution
{
public:
    class Comp
    {
    public:
        bool operator()(const pair<int, int> &a, const pair<int, int> &b)
        {
            return a.second > b.second;
        }
    };

    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        vector<int> dist(n + 1, INT_MAX);
        vector<vector<pair<int, int>>> graph(n + 1); // node, times
        for (auto &v : times)
            graph[v[0]].push_back({v[1], v[2]});

        priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
        dist[k] = 0;
        pq.push({k, 0});
        while (!pq.empty())
        {
            pair<int, int> t = pq.top();
            pq.pop();

            for (auto &neighbor : graph[t.first])
            {
                int next = neighbor.first;
                if (dist[next] > dist[t.first] + neighbor.second)
                {
                    dist[next] = dist[t.first] + neighbor.second;
                    pq.push({next, dist[next]});
                }
            }
        }
        int ans = dist[k];
        for (int i = 1; i < n + 1; i++)
            ans = max(dist[i], ans);
        return ans == INT_MAX ? -1 : ans;
    }
};