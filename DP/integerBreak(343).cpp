class Solution
{
public:
    int integerBreak(int n)
    {
        vector<int> memo(n + 1, 0);
        for (int i = 2; i <= n; i++)
        {
            int mid = i / 2;
            for (int k = 1; k <= mid; k++)
            {
                int left = k < memo[k] ? memo[k] : k;
                int right = i - k < memo[i - k] ? memo[i - k] : i - k;
                memo[i] = max(memo[i], left * right);
            }
        }
        return memo.back();
    }
};
// 8 = 4 4 , 3 3 2