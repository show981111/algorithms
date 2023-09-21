/**
 * How do I know it's DP? Looks like sub problem keeps repeating!
 * T(N) : Maximum product by integer break
 * T(N) = max(T(N-k), N-k) * max(T(k), k)
 *         T(N-k) is product of broken down integer. It might be smaller than whole integer, so choose bigger one!
 */

class Solution
{
public:
    int integerBreak(int n)
    {
        vector<int> memo(n + 1, 0);
        memo[1] = 1;

        for (int i = 2; i <= n; i++)
        {
            for (int k = 1; k <= i / 2; k++)
            {
                memo[i] = max(memo[i], max(memo[i - k], i - k) * max(memo[k], k));
            }
        }
        return memo.back();
    }
};