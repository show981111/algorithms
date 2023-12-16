/*
T(i,H) = max(T(i-1,H), T(i-1,S) - prices[i])
T(i,S) = max(T(i-1,S), T(i, H) + prices[i] - fee)
*/

class Solution
{
public:
    struct State
    {
        int hold;
        int sold;
    };
    int maxProfit(vector<int> &prices, int fee)
    {
        vector<State> dp(prices.size());
        dp[0].hold = -prices[0];
        dp[0].sold = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            dp[i].hold = max(dp[i - 1].hold, dp[i - 1].sold - prices[i]);
            dp[i].sold = max(dp[i - 1].sold, dp[i].hold + prices[i] - fee);
            // cout << dp[i].sold << " ";
        }

        return dp.back().sold;
    }
    /**
     * O(1) space version
     */
    int maxProfit(vector<int> &prices, int fee)
    {
        int hold = -prices[0];
        int sold = 0;

        for (int i = 1; i < prices.size(); i++)
        {
            hold = max(hold, sold - prices[i]);
            sold = max(sold, hold + prices[i] - fee);
        }

        return sold;
    }
};