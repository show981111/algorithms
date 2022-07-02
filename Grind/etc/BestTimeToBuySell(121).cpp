/**
 * @brief This is just getting a max difference
 *
 */

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int buy = INT_MAX;
        int potBuy = INT_MAX;
        int sell = -1;
        for (int price : prices)
        {
            if (sell == -1)
            { // sell price is not set
                if (buy > price)
                    buy = price;
                else
                    sell = price;
            }
            else
            {                                           // sell price is set
                if (sell < price)                       // if cur price is bigger than cur sell, change sell
                    sell = price;                       // buy < sell < price
                else if (buy > price && potBuy > price) // sell >= price,
                    potBuy = price;

                if (price - potBuy > sell - buy)
                {
                    sell = price;
                    buy = potBuy;
                    potBuy = INT_MAX;
                }
            }
        }
        return (sell != -1) ? sell - buy : 0;
    }
};

/**
 * @brief Better solution
 * We are saving the max profit as we traverse.
 * We update minPrice to reflect the potential buyPrice.
 * If we see the bigger price gap after the max profit was set, we update maxPro
 */

int maxProfit(vector<int> &prices)
{
    int maxPro = 0;
    int minPrice = INT_MAX;
    for (int i = 0; i < prices.size(); i++)
    {
        minPrice = min(minPrice, prices[i]);
        maxPro = max(maxPro, prices[i] - minPrice);
    }
    return maxPro;
}