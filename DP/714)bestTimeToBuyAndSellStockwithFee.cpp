/**
 * @brief One key of DP...
 * What we can do now!
 * Can we make a decision based on what we do before? => recurrence relation?
 * YES DP!
 *
 * In this case,
 * At time "i", we can sell or buy or do nothing.
 *
 * We can think of sell state as we do not currently hold anything
 * We can think of buy state as we currently hold something
 *
 * In case of sell, what can we do?
 *  -> we just do nothing(use previous sold)   (sold)
 *  -> or we can sell what we bought!          (bought +prices[i] - fee)
 * In case of buy,
 *  -> we can keep holding what we bought      (bought)
 *  -> or we can buy current product!          (sold - prices[i]) or (sold - prices[i] - fee)
 *                                             (should sell before we buy anything)
 * Fee can go either way, when we sell it? or buy it?
 */

class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int sold = 0;
        int bought = -prices[0];
        int N = prices.size();
        int maxProfit = 0;
        for (int i = 1; i < N; i++)
        {
            sold = max(sold, bought + prices[i] - fee);
            bought = max(bought, sold - prices[i]);
        }

        return sold;
    }
};