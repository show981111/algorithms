/**
 * @brief Classic DP
 * Coins : a_1, a_2 ... a_k
 * T(n) = min(T(n-a_1), T(n-a_2), ..., T(n-a_k))
 *
 */

class Solution
{
public:
    // T(n) = min(T(n-k)); n is amount
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> amountMemo(amount + 1, 0);
        // amountMemo[0] = 1;
        for (int curAmount = 1; curAmount <= amount; curAmount++)
        {
            int ways = amount + 1;
            for (int coin : coins)
            {
                if (curAmount - coin >= 0 && amountMemo[curAmount - coin] != -1)
                { // if T(n-k) was possible
                    ways = min(ways, amountMemo[curAmount - coin] + 1);
                }
                // cout << "ways " << ways << " ";
            }
            if (ways != amount + 1)
                amountMemo[curAmount] = ways;
            else
                amountMemo[curAmount] = -1;
            // cout << curAmount << " " <<  amountMemo[curAmount] << endl;
        }

        return amountMemo.back();
    }
};

// Greedy doesn't work because there are cases where greedy cannot find the answer
// ex) [3,7] , 15

/**
 * @brief Shorter
 *
 */

class Solution
{
public:
    // T(n) = min(T(n-k)); n is amount
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> amountMemo(amount + 1, amount + 1);
        amountMemo[0] = 0;

        for (int curAmount = 1; curAmount <= amount; curAmount++)
        {
            for (int coin : coins)
            {
                if (curAmount - coin >= 0 && amountMemo[curAmount - coin] != -1)
                {
                    amountMemo[curAmount] = min(amountMemo[curAmount], amountMemo[curAmount - coin] + 1);
                }
                // cout << "ways " << ways << " ";
            }
            if (amountMemo[curAmount] == amount + 1)
                amountMemo[curAmount] = -1;
            // cout << curAmount << " " <<  amountMemo[curAmount] << endl;
        }

        return amountMemo.back();
    }
};

// Greedy doesn't work because there are cases where greedy cannot find the answer
// ex) [3,7] , 15