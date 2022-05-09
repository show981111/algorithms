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
    void bfsMaxLength(vector<vector<int> > &grid, int row, int col)
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
    int orangesRotting(vector<vector<int> > &grid)
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