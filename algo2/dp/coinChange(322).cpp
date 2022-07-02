/**
 * @brief
 * Making a target amount! N is now amount, not the number of coins!
 * When we have two concepts, we should think which one should we use to make a
 * memo.
 *
 * T(M) = min(T(M-k)) + 1 (where k is each coins)
 * So our memo is memo[M] = the least number of coins to make M amount
 */

// Greedy doesn't work because there are cases where greedy cannot find the answer
// ex) [3,7] , 15
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount == 0)
            return 0;
        vector<int> memo(amount + 1, INT_MAX);
        for (int coin : coins)
        {
            if (coin <= amount)
                memo[coin] = 1;
        }
        memo[0] = 0;
        for (int i = 0; i <= amount; i++)
        {
            int res = INT_MAX;
            for (int coin : coins)
            {
                if (i - coin >= 0 && memo[i - coin] != INT_MAX)
                    res = min(res, memo[i - coin]);
            }
            if (res == INT_MAX)
                continue;
            memo[i] = res + 1;
        }
        // for(int i : memo)
        //     cout << i << " ";
        // cout << endl;
        if (memo.back() == INT_MAX)
            return -1;
        return memo.back();
    }
};