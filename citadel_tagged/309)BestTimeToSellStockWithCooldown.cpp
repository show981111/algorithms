class Solution
{
public:
    /*
        T(i, H) = Suppose I am holding a stock at I_th day. Max profit?
        T(i, S) = MAX sold profit at I_th day

        T(i, H) = max(T(i-1,H), T(i-2,S) - prices[i], T(i-1,N) - prices[i]);
        T(i, N) = max(T(i-1,N), T(i-1, S)); => Best profit when doing nothing
        T(i, S) = T(i,  H) + prices[i]; => Profit if I sell current stock

        Why cannot use
            T(i, S) = max(T(i-1,S), T(i,  H) + prices[i]); ?
            In this case, at I_th day, we might not sell any stock if T(i-1,S) is bigger.
            Then, when we calculate T(i+1,H), we just assume that at T(i,S) we sold the stock.
            Thus, we need to separate from not selling anything + Actually sold something.
    */
    struct Profit
    {
        int hold;
        int sold;
        int none;
    };
    int maxProfit(vector<int> &prices)
    {
        vector<Profit> dp(prices.size());
        dp[0].hold = -prices[0];

        for (int i = 1; i < prices.size(); i++)
        {
            dp[i].hold = max(dp[i - 1].hold, dp[i - 1].none - prices[i]);
            dp[i].none = max(dp[i - 1].none, dp[i - 1].sold);
            if (i - 2 >= 0)
            {
                dp[i].hold = max(dp[i].hold, dp[i - 2].sold - prices[i]);
            }
            dp[i].sold = dp[i].hold + prices[i];
        }
        // return dp.back().sold;
        return max(dp.back().sold, dp.back().none);
    }
};