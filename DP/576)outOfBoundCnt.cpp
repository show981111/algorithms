class Solution
{
public:
    /*
    We can go back to the spot we came from.
    Thus, should approach DP! since we will go to that spot multiple times!

    EX) A > B > D (At D with 2 moves) == A > C > D (At D with 2 moves)
    (A B)
    (C D)

    T(i,j,m) = from grid[i][j], ways to get outside within "m" moves
    T(i,j,m) = T(i+1,j,m-1) + T(i-1,j,m-1) + T(i,j+1,m-1) + T(i,j-1,m-1);

    No dependency between recurrence relations since moves are keep decreasing.
    Even tho the spot is overlapped.
    */
    typedef pair<int, int> Point;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    const int MOD = 1e9 + 7;
    int getWays(const int m, const int n, vector<vector<vector<int>>> &dp, int r, int c, int moves)
    {
        if ((r < 0 || r >= m || c < 0 || c >= n))
            return 1;
        if (moves <= 0)
            return 0;
        if (dp[r][c][moves] != -1)
            return dp[r][c][moves];

        return dp[r][c][moves] = (((getWays(m, n, dp, r - 1, c, moves - 1) % MOD) +
                                   (getWays(m, n, dp, r + 1, c, moves - 1) % MOD)) %
                                      MOD +
                                  ((getWays(m, n, dp, r, c - 1, moves - 1) % MOD) +
                                   (getWays(m, n, dp, r, c + 1, moves - 1) % MOD)) %
                                      MOD) %
                                 MOD;
    }

    int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
    {
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove + 1, -1)));
        return getWays(m, n, dp, startRow, startColumn, maxMove);
    }
};