/**
 * @brief Linear Sliding Window
 *
 * Moving sliding window like this!
 * curSum += nums[right++]
 * curSum -= nums[left++]
 */

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int curSum = 0;
        int minLength = nums.size() + 1;
        int left = 0, right = 0;

        while (left <= right)
        {
            if (curSum < target)
            {
                if (right == nums.size())
                    break;
                curSum += nums[right++];
            }
            else
            { // meets conidition, target <= curSum
                minLength = min(minLength, right - left);
                // cout << left << " " << right << endl;
                if (left == nums.size())
                    break;
                curSum -= nums[left++];
            }
        }
        return minLength == nums.size() + 1 ? 0 : minLength;
    }
};