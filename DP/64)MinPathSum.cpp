/**
 * Can only go right and down.
 *
 * Thus, T(x,y) = min path sum from 0,0 -> x,y
 * Is, T(x,y) = min(T(x-1,y), T(x,y-1)) + grid[x][y]
 *
 */

class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (i == 0 && j == 0)
                    continue;
                else if (i == 0)
                    grid[i][j] += grid[i][j - 1];
                else if (j == 0)
                    grid[i][j] += grid[i - 1][j];
                else
                {
                    grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
                }
            }
        }

        return grid.back().back();
    }
};