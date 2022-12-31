class Solution
{
public:
    /** X = -inf
                    1   2        3           0   2
Profit (0)REST  0   0   0        1           2   2
        1(sell) 0   0   1(sold)  2(sold)     1   3
        2(buy)  0  -1  -1        -1          1   2


                -1 vs -2 => T[N][2] = T[N-1][0] - curPrice vs T[N-1][2]
                       Rest prev - and buy today vs Dont buy today
                            T[N][1] = T[N][2] + curPrice
                            T[N][0] = max(T[n-1][1], T[n-1][0]). (sold prev vs do nothingp rev)
    */
    int maxProfit(vector<int> &prices)
    {
        int rest = 0, sold = 0, buy = -prices[0];
        int ans = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            buy = max(rest - prices[i], buy); // rest prev and buy today vs don't buy
            rest = max(sold, rest);           // sold yesterday vs rest
            sold = buy + prices[i];           // Buy and Sell in the same day!
            ans = max(rest, max(buy, sold));
            // cout << rest << " " << sold << " " << buy << endl;
        }
        return ans;
    }
};