/**
 * We have a limit in terms of transaction.
 * Now the problem becomes complicated because
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems
 *
 */

class Solution
{
public:
    /*
        3.     3.   5.   0 0 0 3 1 4
    0. (0,0) (0,0).(0,0)
    1  (-3,0) (-3,0) (-3,2) (0,0)
    2

    dp[k][i].hold = max(dp[k][i-1].hold, dp[k-1][i-1].sold + stock[i])
    dp[k][i].sold = max(dp[k][i-1].sold, dp[k][i].hold + stock[i])
    */
    struct State
    {
        int hold = 0;
        int sold = 0;
    };
    int maxProfit(vector<int> &prices)
    {
        vector<vector<State>> dp(3, vector<State>(prices.size()));
        dp[1][0] = State{-prices[0], 0};
        dp[2][0] = State{-prices[0], 0};

        for (int tx = 1; tx <= 2; tx++)
        {
            for (int i = 1; i < prices.size(); i++)
            {
                dp[tx][i].hold = max(dp[tx][i - 1].hold, dp[tx - 1][i - 1].sold - prices[i]);
                dp[tx][i].sold = max(dp[tx][i - 1].sold, dp[tx][i].hold + prices[i]);
            }
        }
        return dp[2][prices.size() - 1].sold;
    }
};