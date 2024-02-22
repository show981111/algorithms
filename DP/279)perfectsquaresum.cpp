/**
 * Partition OR Brute force counting => DP!
 *
 * We will probably have to re-use the previous counting for future's counting result!
 * Top-Down
 */
class Solution
{
public:
    /*
    T(N) = Least number represented as a sum of squares
    T(N) = T(N-1) or T(N-2*2) or T(N-3*3)
    */
    int solve(vector<int> &dp, int n)
    {
        if (n < 0)
            return -1;
        if (dp[n] != -1)
            return dp[n];

        int i = 1;
        int minLength = n;
        while (n - i * i >= 0)
        {
            minLength = min(minLength, solve(dp, n - i * i));
            if (minLength == 0)
                break;
            i++;
        }
        return dp[n] = minLength + 1;
    }
    int numSquares(int n)
    {
        vector<int> dp(n + 1, -1);
        dp[0] = 0;

        return solve(dp, n);
    }
};
/**
 * Bottom up
 */
int numSquares(int n)
{
    vector<int> dp(n + 1, n);
    dp[1] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (ceil(sqrt(i)) * ceil(sqrt(i)) == (double)i)
        {
            dp[i] = 1;
        }
        dp[i] = min(dp[i], i); // this point, dp[i] should be optimal
        int off = 1;
        while (i + off * off <= n)
        {
            dp[i + off * off] = min(dp[i + off * off], dp[i] + 1);
            off++;
        }
    }

    return dp.back();
}