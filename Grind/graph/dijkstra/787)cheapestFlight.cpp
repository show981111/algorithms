/**
 * @brief Variation of Dijkstra but gives TLE
 *
 * We want to know the shortest path from SRC within K nodes.
 * Thus, we cannot just use visited node and dist node, and prune the bigger edges
 * because it is possible that, we reach that node in K nodes, and result in shorter distance.
 * EX) A -> ,,, B -> ,,, C , K = 5;
 * If we reach B in 5 nodes and dist[B] = 10. if this is the minimum, then we cannot
 * use this to go to C because we already used all K nodes to get there.
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
    class Comp
    {
    public:
        bool operator()(const Edge &a, const Edge &b)
        {
            return a.cost > b.cost;
        }
    };

    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        vector<vector<pair<int, int>>> graph(n); // to, cost
        for (auto &f : flights)
        {
            graph[f[0]].push_back({f[1], f[2]});
        }
        priority_queue<Edge, vector<Edge>, Comp> pq;
        pq.push(Edge(src, 0, 0));

        while (!pq.empty())
        {
            Edge t = pq.top();
            // cout << t.to << " " << t.cost << " " << t.stops << endl;
            pq.pop();
            if (t.to == dst)
                return t.cost;
            if (t.stops > k)
                continue;
            for (int i = 0; i < graph[t.to].size(); i++)
            {
                int next = graph[t.to][i].first;
                int newDist = t.cost + graph[t.to][i].second;
                pq.push(Edge(next, newDist, t.stops + 1));
            }
        }
        return -1;
    }
};