/**
 * @brief DP
 * Just dividing cases!
 * If there are more constraints, then we should divide cases according to that
 * constraints. The key is each case should be independant!
 *
 */

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        vector<int> memo(nums.size());
        if (nums.size() == 0)
            return 0;
        else if (nums.size() == 1)
            return nums[0];
        else if (nums.size() == 2)
            return max(nums[0], nums[1]);
        else if (nums.size() == 3) // 1 > n - 2
            return max(nums[1], max(nums[0], nums[2]));
        // first case : 0 ~ n-1
        memo[0] = nums[0];
        memo[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size() - 1; i++)
        {
            memo[i] = max(memo[i - 2] + nums[i], memo[i - 1]);
        }
        int from0 = memo[nums.size() - 2];
        //  second case : 1 ~ n - 2 + nums[n]
        memo[1] = nums[1];
        memo[2] = max(nums[1], nums[2]);
        for (int i = 3; i < nums.size() - 2; i++)
        {
            memo[i] = max(memo[i - 2] + nums[i], memo[i - 1]);
        }
        return max(from0, memo[nums.size() - 3] + *nums.rbegin());
    }
};