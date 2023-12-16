/**
 * Bottom-up DP
 *
 * T(N, d) :number of n-length numbers we can generate that ends with digit "d"
 *
 * T(N, d) = SUM(T(N-1,k)) where k is the digit that knight can arrive at d.
 *
 * Thus, when the digit ends with 'd' at N-1, we should add T(N-1,d) to all T(N,k) where k is the digit that we can arrive from d.
 *
 * T(N,d) is overlapping if we do recursion.
 * Why? T(N, d) -> T(N-1,k) -> ... there are lots of ways we can arrive at T(N-a,k) so top down dp will hitting this spot frequently.
 */

class Solution
{
public:
    bool isValid(int row, int col, vector<vector<int>> &pad)
    {
        return row >= 0 && row < 4 && col >= 0 && col < 3 && pad[row][col] >= 0;
    }
    const int MOD = 1e9 + 7;

    pair<int, int> getLoc(int d)
    {
        if (d == 0)
        {
            return {3, 1};
        }
        else
        {
            int r = (d - 1) / 3;
            int c = (d - 1) % 3;
            return {r, c};
        }
    }
    int knightDialer(int n)
    {
        vector<vector<int>> pad = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};
        vector<vector<int>> dir = {{-2, 1}, {-2, -1}, {2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        vector<vector<int>> memo(n + 1, vector<int>(10, 0));
        for (int i = 0; i < 10; i++)
            memo[1][i] = 1;

        vector<vector<int>> canGoFrom(10);
        for (int i = 0; i < 10; i++)
        {
            pair<int, int> loc = getLoc(i);
            for (int d = 0; d < 8; d++)
            {
                int nextR = loc.first + dir[d][0];
                int nextC = loc.second + dir[d][1];
                if (isValid(nextR, nextC, pad))
                {
                    canGoFrom[i].push_back(pad[nextR][nextC]);
                }
            }
        }

        for (int length = 2; length <= n; length++)
        {
            for (int endingWith = 0; endingWith <= 9; endingWith++)
            {
                for (int i = 0; i < canGoFrom[endingWith].size(); i++)
                {
                    memo[length][canGoFrom[endingWith][i]] += memo[length - 1][endingWith];
                    memo[length][canGoFrom[endingWith][i]] %= MOD;
                }
            }
        }

        int sum = 0;
        for (int i = 0; i <= 9; i++)
        {
            sum = (sum + memo[n][i]) % MOD;
        }
        return sum;
    }
};

/**
 * Redursive with memoization
 */

class Solution
{
public:
    bool isValid(int row, int col, vector<vector<int>> &pad)
    {
        return row >= 0 && row < 4 && col >= 0 && col < 3 && pad[row][col] >= 0;
    }
    const int MOD = 1e9 + 7;

    pair<int, int> getLoc(int d)
    {
        if (d == 0)
        {
            return {3, 1};
        }
        else
        {
            int r = (d - 1) / 3;
            int c = (d - 1) % 3;
            return {r, c};
        }
    }

    int dfs(int n, int curNumber, vector<vector<int>> &canGoFrom, vector<vector<int>> &memo)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        if (memo[n][curNumber] != -1)
            return memo[n][curNumber];

        int ans = 0;
        for (int nextNum : canGoFrom[curNumber])
        {
            ans += dfs(n - 1, nextNum, canGoFrom, memo);
            ans %= MOD;
        }
        return memo[n][curNumber] = ans;
    }
    int knightDialer(int n)
    {
        vector<vector<int>> pad = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};
        vector<vector<int>> dir = {{-2, 1}, {-2, -1}, {2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        vector<vector<int>> memo(n + 1, vector<int>(10, -1));
        for (int i = 0; i < 10; i++)
            memo[1][i] = 1;

        vector<vector<int>> canGoFrom(10);
        for (int i = 0; i < 10; i++)
        {
            pair<int, int> loc = getLoc(i);
            for (int d = 0; d < 8; d++)
            {
                int nextR = loc.first + dir[d][0];
                int nextC = loc.second + dir[d][1];
                if (isValid(nextR, nextC, pad))
                {
                    canGoFrom[i].push_back(pad[nextR][nextC]);
                }
            }
        }
        int sum = 0;
        for (int i = 0; i <= 9; i++)
        {
            sum += dfs(n, i, canGoFrom, memo);
            sum %= MOD;
        }
        return sum;
    }
};