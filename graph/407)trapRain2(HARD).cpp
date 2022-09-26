/**
 * @brief Priority Queue and BFS.
 * PQ for calculate minimum height of surroundings.
 * BFS to get how much rain we can get with current Min.
 * https://leetcode.com/problems/trapping-rain-water-ii/discuss/1138028/Python3Visualization-BFS-Solution-With-Explanation
 */

class Solution
{
public:
    struct Coord
    {
        int height;
        int row;
        int col;
        Coord(int h, int r, int c) : height(h), row(r), col(c) {}
    };
    struct Comp
    {
        bool operator()(const Coord &a, const Coord &b)
        {
            return a.height > b.height;
        }
    };
    typedef priority_queue<Coord, vector<Coord>, Comp> CoordPQ;
    void addEdge(vector<vector<int>> &heightMap, CoordPQ &pq)
    {
        int N = heightMap.size(), M = heightMap[0].size();

        for (int i = 0; i < N; i++)
        {
            pq.push({heightMap[i][0], i, 0});
            pq.push({heightMap[i][M - 1], i, M - 1});
            heightMap[i][0] = -1;
            heightMap[i][M - 1] = -1;
        }
        for (int j = 1; j < M - 1; j++)
        {
            pq.push({heightMap[0][j], 0, j});
            pq.push({heightMap[N - 1][j], N - 1, j});
            heightMap[0][j] = -1;
            heightMap[N - 1][j] = -1;
        }
    }

    void bfs(vector<vector<int>> &heightMap, int row, int col, int curHeight, CoordPQ &pq, int &ans)
    {
        int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        queue<pair<int, int>> q;
        q.push({row, col});
        heightMap[row][col] = -1; // visited

        while (!q.empty())
        {
            pair<int, int> cur = q.front();
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.first + dir[i][0];
                int nextCol = cur.second + dir[i][1];
                if (nextRow >= 0 && nextRow < heightMap.size() && nextCol >= 0 && nextCol < heightMap[0].size() && heightMap[nextRow][nextCol] != -1)
                {
                    // if height is smaller than current height, we can trap rain.
                    // since "curHeight" is the smallest height, we can assure that
                    // we can trap this amount of water
                    if (heightMap[nextRow][nextCol] < curHeight)
                    {
                        // cout << curHeight << " " << nextRow << " " << nextCol << endl;
                        ans += (curHeight - heightMap[nextRow][nextCol]);
                        q.push({nextRow, nextCol});
                    }
                    else if (heightMap[nextRow][nextCol] >= curHeight)
                    {
                        // if it is higher than curren height, we should put it into PQ
                        // because we should start BFS from this position again to find
                        // how much rain we can get
                        pq.push({heightMap[nextRow][nextCol], nextRow, nextCol});
                    }
                    heightMap[nextRow][nextCol] = -1;
                }
            }
        }
    }

    int trapRainWater(vector<vector<int>> &heightMap)
    {
        int N = heightMap.size();
        int M = heightMap[0].size();
        priority_queue<Coord, vector<Coord>, Comp> pq;
        addEdge(heightMap, pq);
        int ans = 0;
        while (!pq.empty())
        {
            Coord cur = pq.top();
            pq.pop();
            // Starting from current height, do BFS to
            // get rains with current height
            bfs(heightMap, cur.row, cur.col, cur.height, pq, ans);
        }

        return ans;
    }
};