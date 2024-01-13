/**
 * https://leetcode.com/problems/maximum-sum-circular-subarray/editorial/
 * Maximum subarray sum.
 *
 * We compare, prefix ending here vs nums[i] (here, prefix does not have to start at 0 index.)
 *
 * T(i) = max prefix ending here
 * T(i) = max(T(i-1) + nums[i], nums[i]).
 *
 * Now we know max prefix ending at i_th index, we just do max of all T(i) from 0 ~ N.
 *
 * This way, we can get a regular max sum that is in the middle of the array [ ----- ]
 *
 * Now, how to get the circular sum?
 * Circular sum looks like, [--- X Y Z ----]. EX) [1 2 3 -10 -10 3 2 1] => Max circualr array subarray sum is, [3 2 1 1 2 3]
 * So, it looks like, prefix starting from 0 and suffix starting from N.
 * Thus, max prefix + max suffix can be a candidate!
 *
 */
class Solution
{
public:
    int maxSubarraySumCircular(vector<int> &nums)
    {
        int maxEndingHere = nums[0];
        int maxSum = nums[0];
        int totalSum = nums[0];
        int leftMax = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            maxEndingHere = max(maxEndingHere + nums[i], nums[i]);
            maxSum = max(maxSum, maxEndingHere);
            totalSum += nums[i];
        }
        // get a regular max subarray sum that is in the middle of the array

        int leftSum = nums[0];    // prefix sum starting from 0-index
        int maxLeftSum = nums[0]; // max prefix starting from 0-index
        for (int i = 1; i < nums.size(); i++)
        {
            leftSum += nums[i];                    // keep accumulating left prefix
            maxLeftSum = max(maxLeftSum, leftSum); // take max. It can skip elements! ex) [1 2 3 -1 -1 -1 ... ] we do not want to include -1's

            maxSum = max(maxSum, maxLeftSum + totalSum - leftSum); // Right sum = totalSum - leftSum = sum[i+1:N]
        }
        return maxSum;
    }
};