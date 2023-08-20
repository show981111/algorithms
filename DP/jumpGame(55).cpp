/**
 * @brief Record the max Index it can reach
 *
 */

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        if (nums.size() <= 1)
            return true;
        int maxLength = 0;

        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (i <= maxLength)
            {
                maxLength = max(maxLength, i + nums[i]);
                if (maxLength >= nums.size() - 1)
                    return true;
            }
        }
        return false;
    }
};