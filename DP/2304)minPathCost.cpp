/**
 * Usually bottom up is easy to code.
 * If you think u need a backTrack, just trying to write a recursive relation.
 * If recursive relation does have an overlap => DP
 */

class Solution
{
public:
    /*
    T(r,c): At row r, col c, MIN PATH COST
    T(r,c) = min(T(r-1,0) + dist(r-1,0 ~ r,c), T(r-1,1) + dist(r-1,1 ~ r,c), ...,
                                            T(r-1, ColSize - 1) + dist(r-1,ColSize - 1 ~ r,c)) + grid[r][c]

    BASE T(0,c) = grid[0][c]

    TC: O(R*C*C)
    5 3
    4 0
    2 1
    */
    int minPathCost(vector<vector<int>> &grid, vector<vector<int>> &moveCost)
    {
        const int colSize = grid[0].size();
        const int rowSize = grid.size();
        int maxCost = 100 * 50 * 50 * 2500; // (max move cost * max row size * max col size * max grid val)
        vector<vector<int>> memo(grid.size(), vector<int>(grid[0].size(), maxCost));
        for (int c = 0; c < colSize; c++)
        {
            memo[0][c] = grid[0][c];
        }

        for (int r = 1; r < rowSize; ++r)
        {
            for (int c = 0; c < colSize; ++c)
            {
                for (int cc = 0; cc < colSize; ++cc)
                {
                    memo[r][c] = min(memo[r][c], memo[r - 1][cc] + moveCost[grid[r - 1][cc]][c]);
                }
                memo[r][c] += grid[r][c];
            }
        }
        int minPathCost = maxCost;
        for (int c = 0; c < colSize; c++)
        {
            minPathCost = min(minPathCost, memo[rowSize - 1][c]);
        }
        return minPathCost;
    }
};

/**
 * Recursive
 */

class Solution
{
public:
    vector<vector<int>> memo;
    int BackTrack(vector<vector<int>> &grid, vector<vector<int>> &moveCost, int row, int col, const int defaultValue)
    {
        if (row == 0)
        {
            return memo[row][col] = grid[row][col];
        }

        if (memo[row][col] != defaultValue)
            return memo[row][col];

        for (int c = 0; c < grid[0].size(); c++)
        {
            memo[row][col] = min(memo[row][col], BackTrack(grid, moveCost, row - 1, c, defaultValue) + moveCost[grid[row - 1][c]][col]);
        }
        memo[row][col] += grid[row][col];
        return memo[row][col];
    }
    int minPathCost(vector<vector<int>> &grid, vector<vector<int>> &moveCost)
    {
        const int colSize = grid[0].size();
        const int rowSize = grid.size();
        int maxCost = 100 * 50 * 50 * 2500; // (max move cost * max row size * max col size * max grid val)
        memo.resize(grid.size(), vector<int>(grid[0].size(), maxCost));

        int ans = maxCost;
        for (int c = 0; c < colSize; c++)
        {
            ans = min(ans, BackTrack(grid, moveCost, rowSize - 1, c, maxCost));
        }
        return ans;
    }
};