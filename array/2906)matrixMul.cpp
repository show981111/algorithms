/**
 * Cannot Add all of them or Multiply all of them due to overflow.
 * Use Prefix & Suffix!
 *
 * 1 2 3 4 [5] 6 7 8 9
 *
 * If I want to calculate SUM[:N] - arr[i] = prefix[i-1] + suffix[i+1]
 */

class Solution
{
public:
    int modMul(int a, int b)
    {
        return ((a % 12345) * (b % 12345)) % 12345;
    }
    vector<vector<int>> constructProductMatrix(vector<vector<int>> &grid)
    {
        vector<vector<int>> p(grid.size(), vector<int>(grid[0].size(), 0));
        vector<vector<int>> prefix(grid.size(), vector<int>(grid[0].size(), 0));
        vector<vector<int>> suffix(grid.size(), vector<int>(grid[0].size(), 0));

        int R = grid.size();
        int C = grid[0].size();
        prefix[0][0] = grid[0][0];
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                if (j == 0)
                    prefix[i][j] = modMul(prefix[i - 1].back(), grid[i][j]);
                else
                    prefix[i][j] = modMul(prefix[i][j - 1], grid[i][j]);
            }
        }
        suffix[R - 1][C - 1] = grid[R - 1][C - 1];

        for (int i = R - 1; i >= 0; i--)
        {
            for (int j = C - 1; j >= 0; j--)
            {
                int pre = 0, suf = 0;
                if (i == 0 && j == 0)
                {
                    pre = 1;
                }
                else if (i == R - 1 && j == C - 1)
                {
                    suf = 1;
                }
                if (pre != 1)
                    pre = j - 1 >= 0 ? prefix[i][j - 1] : prefix[i - 1].back();
                if (suf != 1)
                    suf = j + 1 < C ? suffix[i][j + 1] : suffix[i + 1][0];

                p[i][j] = modMul(pre, suf);

                if (i == R - 1 && j == C - 1)
                    continue;
                if (j == C - 1)
                    suffix[i][j] = modMul(suffix[i + 1][0], grid[i][j]);
                else
                    suffix[i][j] = modMul(suffix[i][j + 1], grid[i][j]);
            }
        }

        return p;
    }
};