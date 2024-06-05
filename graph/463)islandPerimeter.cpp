class Solution
{
public:
    /*
    How do we know the land that is on the outside? Do we do some graph traversal?
    Think about the definition carefully and come up with the simplest wat!
    Definition of perimeter = the part you touches the water.
    Now, its easy! per each land block, look around, add the neighbors who are water!
    */
    void dfs(vector<vector<int>> &grid, int i, int j, int &perimeter)
    {
        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0];
            int c = j + dir[d][1];
            if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] == 0)
                perimeter += 1;
            else if (grid[r][c] == 1)
            {
                grid[r][c] = -1;
                dfs(grid, r, c, perimeter);
            }
        }
    }
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int perimeter = 0;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    grid[i][j] = -1;
                    dfs(grid, i, j, perimeter);
                    return perimeter;
                }
            }
        }
        return perimeter;
    }
};

/**
 * Or we can just traverse array
 */

class Solution
{
public:
    int checkWater(vector<vector<int>> &grid, int i, int j)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0)
            return 1;
        return 0;
    }
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int perimeter = 0;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    perimeter += checkWater(grid, i - 1, j);
                    perimeter += checkWater(grid, i + 1, j);
                    perimeter += checkWater(grid, i, j - 1);
                    perimeter += checkWater(grid, i, j + 1);
                }
            }
        }
        return perimeter;
    }
};