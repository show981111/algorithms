/**
 * @brief BFS
 * Important thing is, mark visited when u push it!
 * To prevent re-pushing that node later!
 */

class Solution
{
public:
    struct Point
    {
        int r;
        int c;
    };
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void bfs(vector<vector<char>> &grid, int row, int col)
    {
        queue<Point> q;
        q.push(Point{row, col});
        grid[row][col] = 'X';

        while (!q.empty())
        {
            Point f = q.front();
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int curRow = f.r + dir[i][0];
                int curCol = f.c + dir[i][1];

                if (curRow >= 0 && curRow < grid.size() && curCol >= 0 && curCol < grid[0].size() && grid[curRow][curCol] == '1')
                {
                    q.push(Point{curRow, curCol});
                    grid[curRow][curCol] = 'X';
                }
            }
        }
    }
    int numIslands(vector<vector<char>> &grid)
    {
        int numOfIsland = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == '1')
                {
                    bfs(grid, i, j);
                    numOfIsland++;
                }
            }
        }
        return numOfIsland;
    }
};

class Solution
{
public:
    void dfs(vector<vector<char>> &grid, int row, int col)
    {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] != '1')
            return;
        grid[row][col] = '2';

        dfs(grid, row + 1, col);
        dfs(grid, row - 1, col);
        dfs(grid, row, col + 1);
        dfs(grid, row, col - 1);
    }
    int numIslands(vector<vector<char>> &grid)
    {
        int rowSize = grid.size();
        int colSize = grid[0].size();
        int count = 0;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (grid[i][j] == '1')
                {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
};