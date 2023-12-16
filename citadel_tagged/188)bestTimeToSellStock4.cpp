class Solution
{
public:
    /*
        T(i,k, H) = max(T(i-1,k,H), T(i-1,k-1,S) - prices[i]);
        // should limit how many times we can buy! since buy -> sell.
        T(i,k, S) = max(T(i-1,k,S), T(i,k,H) + prices[i]);
    */
    struct Info
    {
        int hold;
        int sold;
    };
    int maxProfit(int k, vector<int> &prices)
    {
        vector<vector<Info>> dp(k + 1, vector<Info>(prices.size()));
        for (int i = 1; i <= k; i++)
            dp[i][0].hold = -prices[0];

        for (int tx = 1; tx <= k; ++tx)
        {
            for (int i = 1; i < prices.size(); i++)
            {
                dp[tx][i].hold = max(dp[tx][i - 1].hold, dp[tx - 1][i - 1].sold - prices[i]);
                dp[tx][i].sold = max(dp[tx][i - 1].sold, dp[tx][i].hold + prices[i]);
            }
        }

        return dp[k].back().sold;
    }
};

/**
 * Recursive
 */

class Solution
{
public:
    /*
        At i_th day, Two possibility
        So far not holding any stock & didn't use all tx => Buy Stock
        SO far holding some stock => Can sell => SELL
    */
    struct Info
    {
        int hold = -2000;
        int sold = -2000;
    };
    vector<vector<Info>> dp;

    int solve(vector<int> &prices, int tx, int index, bool holding)
    {
        if (tx == 0)
        {
            dp[tx][index].hold = 0;
            dp[tx][index].sold = 0;
            return 0;
        }
        if (index == 0)
        {
            dp[tx][index].hold = -prices[0];
            dp[tx][index].sold = 0;
            if (holding)
                return dp[tx][index].hold;
            else
                return dp[tx][index].sold;
        }

        if (holding)
        {
            if (dp[tx][index].hold != -2000)
                return dp[tx][index].hold;
            int justHolding = solve(prices, tx, index - 1, true);
            int buyCurrent = solve(prices, tx - 1, index - 1, false) - prices[index];
            int bestBuyPosition = max(justHolding, buyCurrent);
            return dp[tx][index].hold = bestBuyPosition;
        }
        else
        {
            if (dp[tx][index].sold != -2000)
                return dp[tx][index].sold;
            int notSelling = solve(prices, tx, index - 1, false);
            int sellCurrent = solve(prices, tx, index, true) + prices[index];
            int bestSellPosition = max(notSelling, sellCurrent);
            return dp[tx][index].sold = bestSellPosition;
        }
    }

    int maxProfit(int k, vector<int> &prices)
    {
        dp.resize(k + 1, vector<Info>(prices.size()));

        return solve(prices, k, prices.size() - 1, false);
    }
};