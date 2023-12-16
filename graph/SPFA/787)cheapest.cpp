/**
 * @brief Sortest Path Faster Algo
 * https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm
 *
 * Improvement version of Bellman Ford.
 * We add edges using BFS, not randomly adding it.
 *
 * The key differnce with dijkstra(TLE) is,
 * we can prune when the distance is bigger.
 * Since it is basically BFS, the number of nodes are stacking sequentially
 *
 *
 */

class Solution
{
public:
    struct Edge
    {
        int to;
        int cost;
        int stops;
        Edge(int t, int c, int s) : to(t), cost(c), stops(s) {}
    };
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        vector<vector<pair<int, int>>> adj(n); // to, cost

        for (int i = 0; i < flights.size(); i++)
            adj[flights[i][0]].push_back({flights[i][1], flights[i][2]});

        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        queue<Edge> q; // to, cost;
        q.push(Edge(src, 0, 0));

        while (!q.empty())
        {
            Edge t = q.front();
            q.pop();

            for (int i = 0; i < adj[t.to].size(); i++)
            {
                int next = adj[t.to][i].first;
                if (dist[next] > t.cost + adj[t.to][i].second && t.stops <= k)
                {
                    dist[next] = t.cost + adj[t.to][i].second;
                    q.push(Edge(next, dist[next], t.stops + 1));
                }
            }
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
