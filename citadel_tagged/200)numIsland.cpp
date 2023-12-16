/**
 * Simple DFS + reusing grid for visiting check.
 */

class Solution
{
public:
    void dfs(vector<vector<char>> &grid, int curRow, int curCol)
    {
        if (curRow < 0 || curRow >= grid.size() || curCol < 0 || curCol >= grid[0].size())
            return;
        if (grid[curRow][curCol] != '1')
            return;
        grid[curRow][curCol] = '_';

        dfs(grid, curRow + 1, curCol);
        dfs(grid, curRow, curCol + 1);
        dfs(grid, curRow - 1, curCol);
        dfs(grid, curRow, curCol - 1);
    }
    int numIslands(vector<vector<char>> &grid)
    {
        int n = 0;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == '1')
                {
                    dfs(grid, i, j);
                    n++;
                }
            }
        }

        return n;
    }
};