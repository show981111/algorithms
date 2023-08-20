// Trial1 => COUNT PERMUTATION

// Suppose we have an answer for T(N-k)
// DP definition: make n amount using all given coins.
// T(N) = SUM(T(N-coins[i])) => dup count cuz 1 + 2 == 2 + 1
// Problem:
//         => When we sum it up, consider.. is ther an overlap?
//             How to make each branch unique?(no dup)
// Base case, T(0) = 1
// why? if we have coin 5, want to make 5.
// T(5) = T(5-5) = 1

// Trial2 => COMBINATION
// make "n" amount using coin[:i]
// DP definition : make n amount using first i coins
// T(i, n) = T(i-1, n)     otherwise
//         = T(i-1, n) + 1 if n is in coins
// T(0, n) = 0 / T(k, 0) = 1

//     0 1 2 3 4 5
// 0.  1 0 0.0 0 0
// 1.  1 1 1 1 1 1
// 2.  1 1 2 2 3 3
// 3.  1 1 2 2 3 4

//     4 = [2] + 2 / 2 + 1 + 1 / 1 + 1 + 1 + 1

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        vector<vector<int>> ways(coins.size() + 1, vector<int>(amount + 1, 0));
        // BASE CASE
        for (int i = 0; i <= coins.size(); i++)
            ways[i][0] = 1; // we can always make amount 0 with 1 way!

        for (int i = 1; i <= coins.size(); i++)
        {
            int curCoin = coins[i - 1];
            for (int j = 1; j <= amount; j++)
            {
                int useThisCoin = 0;
                int onlyUsePrevCoins = ways[i - 1][j];
                if (j - curCoin >= 0)
                {
                    useThisCoin = ways[i][j - curCoin];
                }
                ways[i][j] = useThisCoin + onlyUsePrevCoins;
            }
        }
        return ways.back().back();
    }
};