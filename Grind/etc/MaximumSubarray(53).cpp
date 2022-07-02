#include <algorithm>

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        vector<int> accum(nums.size());
        int curSum = nums[0];
        accum[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                if (curSum < 0)
                    curSum = nums[i]; // reset curSum
                else
                    curSum += nums[i];
            }
            else
            {
                int acc = curSum + nums[i];
                if (acc > 0)
                { // there is a possibility this could be a bigger subarray
                    curSum = acc;
                }
                else
                {
                    curSum = nums[i]; // 0 possibility
                }
            }
            accum[i] = max(curSum, accum[i - 1]);
            // cout << accum[i] << " ";
        }

        return accum.back();
    }
};

/**
 * @brief Shorter version
 * O(1) Space.
 * Regardless of the sign of nums[i], the key is keeping the MAX
 * So, we should compare
 * A) starting over again from current index
 * VS
 * B) keep adding the number to previous accumulated sum
 * Then keep the MAX!
 *
 * For "maxSoFar", we can just keep the max of accumulated sum VS previousMax
 * (maxSoFar denotes the "MAX sum" until current index)
 */

#include <algorithm>

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int curSum = nums[0];
        int maxSoFar = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            curSum = max(curSum + nums[i], nums[i]); // max of accumulated sum.
            // if just current num is bigger, then we should restart accumulating!
            maxSoFar = max(curSum, maxSoFar); // max until current index
            // ex) nums[1:3] could be bigger than nums[1:5] so we just keep the max value!
        }

        return maxSoFar;
    }
};