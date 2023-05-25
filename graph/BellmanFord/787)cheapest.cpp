/**
 * @brief Bellman Ford is just a dynamic programming
 * Iterate max V-1 times,
 * calculate the distance from SRC to DEST using utmost I number of edges
 * Below is the 2D memo version of bellman ford
 *
 */
class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        vector<vector<int>> dist(n, vector<int>(k + 2, INT_MAX)); // shortest distance. dist[row][col], to "row" with "col" num of edges

        dist[src][0] = 0;

        for (int i = 0; i < k + 2; i++)
        {
            dist[src][i] = 0; // reaching the src is always 0!
        }

        for (int i = 0; i <= k; i++)
        {
            for (auto &f : flights)
            {
                int from = f[0];
                int to = f[1];
                int cost = f[2];

                if (dist[from][i] != INT_MAX)
                {
                    dist[to][i + 1] = min(dist[to][i + 1], dist[from][i] + cost);
                }
            }
        }

        return dist[dst][k + 1] == INT_MAX ? -1 : dist[dst][k + 1];
    }
};

/**
 * @brief Failled version due to optimized memo
 *
 */
class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        vector<pair<int, int>> dist(n); // dist, stops
        for (auto &p : dist)
        {
            p.first = INT_MAX;
            p.second = 0;
        }
        dist[src] = {0, 0};

        for (int i = 0; i <= k; i++)
        {
            for (auto &f : flights)
            {
                int from = f[0];
                int to = f[1];
                int cost = f[2];
                if (dist[from].first != INT_MAX && dist[from].second <= i)
                {
                    dist[to].first = min(dist[to].first, dist[from].first + cost);
                    dist[to].second = dist[from].second + 1;
                    cout << to << " " << dist[to].first << " " << dist[to].second << endl;
                }
            }
            cout << "------\n";
        }
        // it fails because the shorter distance with K nodes replace the existing distance
        // Just like Dijkstra

        return dist[dst].first == INT_MAX ? -1 : dist[dst].first;
    }
};