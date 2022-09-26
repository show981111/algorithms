/**
 * https://leetcode.com/problems/swim-in-rising-water/discuss/965631/Java-3-clean-codes%3A-Dijkstra's-algo-PriorityQueue-and-Binary-search
 *
 * @brief 3 solutions
 * 1. Dijkstra -> Find the shortest path!
 *      We can just keep selecting shortest path
 *      The reason this works is we cannot choose a shortest path to V,
 *      after dist[V] is SET (We can only increase it not decrease the distance)
 * 2. PQ + BFS
 *      We put starting point to PQ.
 *      We pop one from PQ and visit every place we can go(BFS).
 *      Meanwhile, if we find somewhere we cannot(higher than current one),
 *      put it into a PQ so that we can start traversing from there later.
 *
 * 3. BinSearch
 *      Since we know that heights are 0 ~ N*M -1,
 *      and if we can travel to the end with T, then we can do it with T + 1,
 *      we can throw away half of it.
 *      binSearch based on [0 , N*M - 1].
 *      For each mid, test if we can reach to the end using DFS.
 *      if we can, (A) decrease the range and try again. => [L, M] We dont do M-1
 *      because M might be the answer. Instead we break when L >= R
 *      if we cannot, (B) incerase the range. [M+1, R]
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

    void bfs(vector<vector<int>> &grid, CoordPQ &pq, int row, int col, int curHeight)
    {
        int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        int N = grid.size(), M = grid[0].size();
        queue<pair<int, int>> q;
        q.push({row, col});

        while (!q.empty())
        {
            pair<int, int> cur = q.front();
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.first + dir[i][0];
                int nextCol = cur.second + dir[i][1];

                if (nextRow >= 0 && nextRow < N && nextCol >= 0 && nextCol < M && grid[nextRow][nextCol] != -1)
                {
                    if (curHeight > grid[nextRow][nextCol])
                    { // we can travel with current height!
                        q.push({nextRow, nextCol});
                    }
                    else
                    { // we cannot travel, so put it into PQ
                        pq.push({grid[nextRow][nextCol], nextRow, nextCol});
                    }
                    grid[nextRow][nextCol] = -1;
                }
            }
        }
    }

    int swimInWater(vector<vector<int>> &grid)
    {
        /*
        Goal is finding the rout from src -> dest with minimum number is included
        */
        CoordPQ pq;
        int N = grid.size(), M = grid[0].size();

        // starting point
        pq.push({grid[0][0], 0, 0});
        grid[0][0] = -1;
        int ans = grid[N - 1][M - 1];
        while (!pq.empty()) // MNlog(MN)
        {
            Coord cur = pq.top();
            pq.pop();
            grid[cur.row][cur.col] = -1;
            bfs(grid, pq, cur.row, cur.col, cur.height);
            // we visited all places we can visit with current height.
            // all "connected positions" with our current path is in PQ.
            // now we just pop the smallest from PQ, and do BFS again.
            // if we can reach the destination, then DONE!
            if (grid[N - 1][M - 1] == -1)
            {
                return max(cur.height, ans);
            }
        }
        return -1;
    }
};
/**
 * @brief Dijkstra
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

    int swimInWater(vector<vector<int>> &grid)
    {
        /*
        Goal is finding the rout from src -> dest with minimum number is included
        */
        CoordPQ pq;
        int N = grid.size(), M = grid[0].size();
        vector<vector<int>> dist(N, vector<int>(M, INT_MAX));
        pq.push({grid[0][0], 0, 0});
        dist[0][0] = 0;
        int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        while (!pq.empty())
        {
            Coord cur = pq.top();
            pq.pop();
            if (cur.row == N - 1 && cur.col == M - 1)
            {
                return dist[cur.row][cur.col];
            }

            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.row + dir[i][0];
                int nextCol = cur.col + dir[i][1];
                // find places we can go with current min height
                if (nextRow >= 0 && nextRow < N && nextCol >= 0 && nextCol < M)
                {
                    // relaxing. we should pick max of current height and the height of dest.
                    int alt = max(cur.height, grid[nextRow][nextCol]);
                    if (alt < dist[nextRow][nextCol])
                    {
                        dist[nextRow][nextCol] = alt;
                        pq.push({alt, nextRow, nextCol});
                    }
                }
            }
        }
        return -1;
    }
};
/**
 * @brief BinSearch
 *
 */
class Solution
{
public:
    bool dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int row, int col, int curHeight)
    {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || visited[row][col])
            return false;
        visited[row][col] = true;
        if (grid[row][col] > curHeight)
            return false;
        if (row == grid.size() - 1 && col == grid[0].size() - 1)
            return true;

        // cout << row << " " << col << endl;
        return dfs(grid, visited, row - 1, col, curHeight) || dfs(grid, visited, row + 1, col, curHeight) || dfs(grid, visited, row, col - 1, curHeight) || dfs(grid, visited, row, col + 1, curHeight);
    }

    int binSearch(vector<vector<int>> &grid, int start, int end)
    {
        if (start >= end)
            return start;
        int mid = start + (end - start) / 2;
        // cout << mid << endl;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
        bool res = dfs(grid, visited, 0, 0, mid);
        if (res)
        {
            return binSearch(grid, start, mid);
        }
        else
        {
            return binSearch(grid, mid + 1, end);
        }
    }
    int swimInWater(vector<vector<int>> &grid)
    {
        /*
        Goal is finding the rout from src -> dest with minimum number is included
        */
        int N = grid.size(), M = grid[0].size();
        return binSearch(grid, max(grid[0][0], grid[N - 1][M - 1]), N * M - 1);
    }
};