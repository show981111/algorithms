/**
 * @brief Buy? or not? in the constraint of one stock... => Knapsack?
 * memo[i] => the maximum profit until i_th day.
 * memo[i] = selling stock in i_th price? = memo[i-1]+prices[i] - prices[i-1];
 *           or not selling. = memo[i-1]
 * in I_th index, we do not possess any stock because we sell it on I_th day or before!
 */

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int N = prices.size();
        vector<int> memo(N, 0);
        for (int i = 1; i < N; i++)
        {
            memo[i] = max(memo[i - 1], memo[i - 1] + prices[i] - prices[i - 1]);
        }
        return memo.back();
    }
};