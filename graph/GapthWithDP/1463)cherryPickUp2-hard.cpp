class Solution
{
public:
    /*
    Path maximazation -> usually require complete search (DP)
    T(cur) = max(T(prev)) + cur_Cherry -> One robot DP

    How to deal with overlap? It is possible that they took different path so
    we cannot just make it 0 =>
    Separate 2 BFS? Taking a max path is 100% beneficial.
    the other robot can take diff path based on first's result
    => Not true. x + y maximization. How to do it?
    [3,1,1] Consider this case, sometimes, one robot should choose non-optimal for itself to maximize the profit of sum.
    [2,5,1] EX) Rob1 -> 3 + 5 + 5 + 2 is the optimal. Now Rob2 can only do 1 + 1 + 5 + 1.
    [1,5,5]     HOWEVER, optimal is, Rob1-> 3 + 2 + 5 + 2, Rob2 -> 1 + 5 + 5 + 1
    [2,1,1] Should choose a path that x + y is max.

    *****
    How to represent, both robot's location in ONE DP cell?
    We cannot do like add both or take max 2 or whateber when the answer is the sum of differen DP cell
    -> Need another dimension!

    Different DP is needed so that we can accomodate both robot's location in one cell of DP!
    dp[i][j][k] = max cherries we can pick when robot A is at (i,j) and B is at (i,k)

    (j-1,j,j+1) or (k-1,k,k+1)
    dp[i][j][k] = (dp[i-1][j-1][k-1] or dp[i-1][j-1][k] or dp[i-1][j-1][k+1]) + grid[i][j] + grid[i][k]
                = (dp[i-1][j][k-1] or dp[i-1][j][k] or dp[i-1][j][k+1])       + grid[i][j] + grid[i][k]
                = (dp[i-1][j+1][k-1] or dp[i-1][j+1][k] or dp[i-1][j+1][k+1]) + grid[i][j] + grid[i][k]
                                                                                if(j == k) only add once
    -> If we use above, then we should start from all positions at bottom level. Since it is going up.

    dp[i][j][k] = (dp[i+1][j-1][k-1] or dp[i+1][j-1][k] or dp[i+1][j-1][k+1]) + grid[i][j] + grid[i][k]
                = (dp[i+1][j][k-1] or dp[i+1][j][k] or dp[i+1][j][k+1])       + grid[i][j] + grid[i][k]
                = (dp[i+1][j+1][k-1] or dp[i+1][j+1][k] or dp[i+1][j+1][k+1]) + grid[i][j] + grid[i][k]
                                                                                if(j == k) only add once
    -> If we use this, we can just do dp[0][0][C-1]. Because we have fixed starting points for robots.
    This recursive pattern is going DOWN.
    */
    int solve(vector<vector<int>> &grid, vector<vector<vector<int>>> &dp, int row, int c1, int c2)
    {
        if (row < 0 || row >= dp.size() || c1 < 0 || c1 >= dp[0].size() || c2 < 0 || c2 >= dp[0].size())
        {
            return 0;
        }
        if (row >= dp.size())
            return 0;
        if (dp[row][c1][c2] != -1)
            return dp[row][c1][c2];

        int m = 0;
        for (int i = -1; i <= 1; i++)
        {
            int nextC1 = c1 + i;
            for (int j = -1; j <= 1; j++)
            {
                int nextC2 = c2 + j;
                m = max(m, solve(grid, dp, row + 1, nextC1, nextC2));
            }
        }
        if (c1 == c2)
        {
            m += grid[row][c1];
        }
        else
        {
            m += grid[row][c1] + grid[row][c2];
        }
        return dp[row][c1][c2] = m;
    }
    int cherryPickup(vector<vector<int>> &grid)
    {
        int R = grid.size(), C = grid[0].size();
        vector<vector<vector<int>>> dp(R, vector<vector<int>>(C, vector<int>(C, -1)));
        return solve(grid, dp, 0, 0, C - 1);
    }
};

/**
 * BFS version
 *
 * Starting from (0,0,C-1) where two robots are at the starting points.
 * Then we proceed to go to neighbors which is 9 possible combinations of 2 robot's positions
 */

struct Points
{
    int r;
    int c1;
    int c2;
    int cherries = 0;
};
int cherryPickup(vector<vector<int>> &grid)
{
    int R = grid.size(), C = grid[0].size();
    vector<vector<vector<int>>> dp(R, vector<vector<int>>(C, vector<int>(C, -1)));
    dp[0][0][C - 1] = grid[0][0] + grid[0].back();
    queue<Points> q;
    q.push(Points{0, 0, C - 1, dp[0][0][C - 1]});
    int m = 0;
    while (!q.empty())
    {
        Points f = q.front();
        m = max(m, f.cherries);
        q.pop();
        if (f.cherries < dp[f.r][f.c1][f.c2])
            continue;
        if (f.r == R - 1)
            continue;

        for (int i = -1; i <= 1; i++)
        {
            int nextC1 = f.c1 + i;
            for (int j = -1; j <= 1; j++)
            {
                int nextC2 = f.c2 + j;
                if (nextC1 < 0 || nextC1 >= C || nextC2 < 0 || nextC2 >= C)
                {
                    continue;
                }

                int alt = f.cherries + grid[f.r + 1][nextC1];
                if (nextC1 != nextC2)
                {
                    alt += grid[f.r + 1][nextC2];
                }

                if (dp[f.r + 1][nextC1][nextC2] < alt)
                {
                    dp[f.r + 1][nextC1][nextC2] = alt;
                    q.push(Points{f.r + 1, nextC1, nextC2, alt});
                }
            }
        }
    }
    return m;
}