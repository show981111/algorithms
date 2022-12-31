/**
 * @brief Can we divide array into two subsets with equal sum?
 *
 * Basically Knapsack
 * 0/1 problem(subset) with constraint(target sum which is Total sum / 2)
 *
 * We can make "j" with 1~i_th element!
 * T(i, j) = T(i-1,j)           ||  T(i-1, j - value[i])
 *           Without Ith element    With Ith element
 *
 */

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        if (nums.size() == 0 || nums.size() == 1)
            return false;

        int totalSum = 0;
        for (auto &n : nums)
            totalSum += n;
        if (totalSum % 2 == 1)
            return false;
        int target = totalSum / 2;

        vector<vector<bool>> memo(nums.size() + 1, vector<bool>(target + 1, false));
        for (int i = 0; i <= nums.size(); i++)
        {
            memo[i][0] = true;
        }
        for (int i = 1; i <= nums.size(); i++)
        {
            for (int j = 1; j <= target; j++)
            {
                memo[i][j] = memo[i - 1][j];
                if (j - nums[i - 1] >= 0)
                {
                    memo[i][j] = memo[i][j] || memo[i - 1][j - nums[i - 1]];
                }
            }
            if (memo[i][target])
                return true;
        }
        return memo[nums.size()][target];
    }
};