/**
 * @brief Maximum Profit with K transaction!
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems
 *
 *
 */

class Solution
{
public:
    /*
             1       2     3     4    5
        0: (0,0)   (0,0) (0,0) (0,0) (0,0)
        1:  -1
        2:  -1
        TXs

        Two state (Have 0 stocks(sold before), 1 stocks(bought before))
        T[k][i] => MAX profit when with K txs
        When should we increment transaction? => When we buy! we cannot buy-sell, buy-sell and buy!
        (SOLD)
        T[k][i].sold = max(T[k][i-1].sold, T[k][i-1].buy + price[i]);
                            Do nothing      Sell what I bought before
        T[k][i].bought = max(T[k][i-1].bought, T[k-1][i].sold - price[i]);
                            Do nothing        sell and buy current!(we can sell and buy at the same time)
                                                (note we use "k-1" because buy consumes one tx)
    */
    struct State
    {
        int bought = 0;
        int sold = 0;
    };
    int maxProfit(vector<int> &prices)
    {
        const int maxTx = 2;
        vector<vector<State>> profits(maxTx + 1, vector<State>(prices.size()));
        for (int i = 1; i <= maxTx; i++)
            profits[i][0].bought = -prices[0];

        for (int tx = 1; tx <= maxTx; tx++)
        {
            for (int j = 1; j < prices.size(); j++)
            {
                profits[tx][j].sold = max(profits[tx][j - 1].sold, profits[tx][j - 1].bought + prices[j]);
                profits[tx][j].bought = max(profits[tx][j - 1].bought, profits[tx - 1][j].sold - prices[j]);
            }
        }
        return profits[maxTx].back().sold;
    }
};