/**
 * @brief Number of path from A to B in Matrix
 * We can use a memo!
 *
 *   1 1 1 1
 * 1 2 3 4 5
 * 1 3 6 10 15
 *
 * Or using math, > > > v v, permutation!
 *
 */

class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> memo(m, vector<int>(n, 1));

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                memo[i][j] = memo[i - 1][j] + memo[i][j - 1];
            }
        }
        return memo[m - 1][n - 1];
    }
};