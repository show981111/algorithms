/*
BFS, run bfs for every rotten oranges
Time : O(V + E) Space : O(V) (queue for BFS)
V = #oranges

Starting from the upper left, if meets rotten orange, run BFS, record distance.
In later's BFS, if the distance is shorter than before, update.
*/

class Solution
{
public:
    struct Point
    {
        int row;
        int col;
        int dis;
    };
    int dir[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}};
    void bfsMaxLength(vector<vector<int>> &grid, int row, int col)
    {
        queue<Point> q;
        q.push({row, col, 0});
        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            grid[cur.row][cur.col] = cur.dis;

            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.row + dir[i][0];
                int nextCol = cur.col + dir[i][1];
                if (nextRow >= 0 && nextRow < grid.size() && nextCol >= 0 && nextCol < grid[0].size() && (grid[nextRow][nextCol] == 1 || cur.dis - 1 > grid[nextRow][nextCol]))
                {
                    grid[nextRow][nextCol] = cur.dis - 1;
                    q.push({nextRow, nextCol, cur.dis - 1});
                }
            }
        }
    }
    int orangesRotting(vector<vector<int>> &grid)
    {
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 2)
                {
                    bfsMaxLength(grid, i, j);
                }
            }
        }
        int minTime = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    return -1;
                }
                else if (minTime > grid[i][j])
                {
                    minTime = grid[i][j];
                }
            }
        }
        return -minTime;
    }
};

/**
 * @brief BFS
 * We are starting a BFS from every rotten orange.
 * The time that is needed to make every orange rotten is
 * the same as the max Depth of this BFS.
 *
 * Thus,
 * 1) put every rotten orange to Queue
 * 2) start BFS and add time when each level is all popped.
 *
 */
class Solution
{
public:
    int dir[4][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int orangesRotting(vector<vector<int>> &grid)
    {
        queue<pair<int, int>> q;
        int rowSize = grid.size();
        int colSize = grid[0].size();
        int freshOrange = 0;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (grid[i][j] == 2)
                    q.push({i, j});
                else if (grid[i][j])
                    freshOrange++;
            }
        }
        int time = q.empty() ? 0 : -1; // since starting is all rotten orange
        while (!q.empty())
        {
            int qSize = q.size();

            for (int i = 0; i < qSize; i++)
            {
                pair<int, int> cur = q.front();
                q.pop();

                for (int j = 0; j < 4; j++)
                {
                    int nextRow = cur.first + dir[j][0];
                    int nextCol = cur.second + dir[j][1];
                    if (nextRow >= 0 && nextRow < rowSize && nextCol >= 0 && nextCol < colSize && grid[nextRow][nextCol] == 1)
                    {
                        grid[nextRow][nextCol] = 2;
                        freshOrange--;
                        q.push({nextRow, nextCol});
                    }
                }
            }
            time++;
            // cout << qSize << endl;
        }
        if (freshOrange > 0)
            return -1;
        return time;
    }
};