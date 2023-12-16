/**
 * Cannot use DP.. why?
 *
 * Suppose N = x + (x+1). Now, let x = a + (a+1). N = a + (a+1) + (x+1), but (a+1) and (x+1) are not consecutive...
 *
 * Now, let's run some examples
 * N = x + (x+1) = 2x+1
 *   = x + (x+1) + (x+2) = 3x + (1+2)
 *   = x+ (x+1) + (x+2) + (x+3) = 4x + (1+2+3)
 *   ...
 *   = x + (x+1) + (x+2) + ... + (x+k) = (k+1)x + (1+2+3+...+k)
 *
 * Now, we can simplify as, If N = (k+1)x + (1+2+3+...+k), N - (1+2+3+...+k) = (k+1)x and if there is a satisfying integer x, then N can be broken down.
 *
 * Using this fact, we can design a simple O(sqrt(N)) algorithm.
 *
 * Why O(sqrt(N))?
 * starting from k = 1,
 * Worst case, n - k(k+1)/2 >= 0. n = k(k+1)/2, k = O(sqrt(n))
 */

class Solution
{
public:
    int consecutiveNumbersSum(int n)
    {
        int k = 1;
        int cnt = 1; // n itself
        int b = 1;

        while (n - b >= k + 1)
        {
            if ((n - b) % (k + 1) == 0)
            {
                cnt++;
            }
            k++;
            b += k;
        }

        return cnt;
    }
};