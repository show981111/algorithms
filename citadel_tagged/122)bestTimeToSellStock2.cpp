class Solution
{
public:
    /*
    T(i,H) = buy i_th stock = max(T(i-1,S) - stock[i], T(i-1,H))
                                Sell prev one and buy one now VS just hold prev one
    T(i,S) = Sell i_th stock = max(T(i,H) + stock[i], T(i-1,S))
                                Sell current one VS just sell prev one
        7  1  5  3 6 4
    H  -7 -1 -1. 1 1 3
    S.  0  0  4. 4 7 7
    */

    int maxProfit(vector<int> &prices)
    {
        vector<vector<int>> dp(2, vector<int>(prices.size()));
        dp[0][0] = -prices[0];
        dp[1][0] = 0;

        for (int i = 1; i < prices.size(); i++)
        {
            dp[0][i] = max(dp[1][i - 1] - prices[i], dp[0][i - 1]);
            dp[1][i] = max(dp[0][i] + prices[i], dp[1][i - 1]);
        }

        return dp[1][prices.size() - 1];
    }

    /**
     * Different version.
     * Keep updating the maxProfit.
     * Wanna buy stock when its low. -> Maximize bought (maxProfit - prices[i]). Since -prices[i], we buy stock when its low.
     * Since we are only subtracting prices[i], we only hold one stock at a time.
     */
    int maxProfit(vector<int> &prices)
    {
        int maxProfit = 0;
        int bought = -prices[0];

        for (int i = 1; i < prices.size(); i++)
        {
            maxProfit = max(maxProfit, bought + prices[i]);
            bought = max(bought, maxProfit - prices[i]);
        }

        return maxProfit;
    }
};