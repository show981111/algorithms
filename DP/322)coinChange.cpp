/**
 * @brief Probably similar to knapsack in terms of
 * we have a constraint(target), but it is not 0/1 because
 * we can choose each coin infinitely
 * So, we just iterate each coin everytime!
 *
 * (2) 2D memo. just like knapsack but choose infinitely!
 *  KEY DIFFERNECE is,
 * KNAPSACK : T(i,j) = T(i-1, j) || T(i-1, j - val[i]); [not use i vs use i]
 * CoinChange : T(i,j) = T(i-1, j) || T(i, j - val[i]); [not use i vs use i but we can use it infinitely]
 *                                                       So, we put i instead of i - 1
 *                                  technically T(i, j-val[i]) vs T(i - 1, j-val[i]) is needed , but
 *                                  T(i, j-val[i]) includes the result of T(i - 1, j-val[i])
 */

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // T(N) = min(T(N-K)) + 1 if N-K < 0, -1
        vector<int> memo(amount + 1, -1);
        memo[0] = 0;
        int N = coins.size();
        for (int target = 1; target <= amount; target++)
        {
            int possibleWays = -1;
            for (int i = 0; i < N; i++)
            {
                int from = target - coins[i];
                if (from >= 0 && memo[from] != -1)
                {
                    if (possibleWays == -1)
                        possibleWays = memo[from] + 1;
                    else
                        possibleWays = min(possibleWays, memo[from] + 1);
                }
            }
            memo[target] = possibleWays;
        }
        return memo.back();
    }
};

// Greedy doesn't work because there are cases where greedy cannot find the answer
// ex) [3,7] , 15

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int N = coins.size();
        vector<vector<int>> memo(N + 1, vector<int>(amount + 1, -1));
        for (int i = 0; i <= N; i++)
        {
            memo[i][0] = 0; // making 0 need 0 coins
        }

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= amount; j++)
            {
                int possibleWays = INT_MAX;
                if (j - coins[i - 1] >= 0 && memo[i][j - coins[i - 1]] != -1)
                {
                    possibleWays = memo[i][j - coins[i - 1]] + 1;
                }
                if (memo[i - 1][j] != -1)
                {
                    possibleWays = min(possibleWays, memo[i - 1][j]);
                }
                if (possibleWays == INT_MAX)
                {
                    memo[i][j] = -1;
                }
                else
                {
                    memo[i][j] = possibleWays;
                }
            }
        }

        return memo[N][amount];
    }
};
