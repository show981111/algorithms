#include <algorithm>
/*
Sliding Window?: When should I stop moving right forward? We dont know...
                Can't stop when we see the negative value cuz there might bigger value
                after that negative value. ex) [1, -1, 1000]
Collect as many positive values as possible,
        as small negative values as possible.
        When we include negative values? when there are positive integers that offsets
        negative value.
=> Optimization problems? -> DP?

T(N) means the maximum subarray sum that includes/ends with arr[N]
DP: T(n) = max(arr[N] + T(N-1), arr[N]) -> Only take current one, or previous one + current one.

Then finally, what we want = max(T(i)) where i = 0 ~ N
It is like LIS!
*/
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int prefix = nums[0];
        int cur = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            if (prefix < 0)
                prefix = max(prefix, nums[i]); // if soFarMax is negative, just take the bigger one. No benefit at adding values. It is better to throw away the prefix with negative sums, and start fresh!
            else                               // if it is positive, we should keep the prefix cuz it is beneficial for us.
                prefix += nums[i];             // regardless of sign, just add in the hope of getting bigger.
            cur = max(cur, prefix);            // Take the max so far.
            // DP: T(n) = max(T(N-1), arr[N] + T(N-1))
        }

        return cur;
    }
};