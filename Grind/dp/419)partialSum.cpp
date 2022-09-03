/**
 * @brief KNAPSACK!
 * We should make a totalSum / 2 using elements in array
 * The key is are we should pick some elements to make the target amount
 * So, we have a choice.
 * Are we picking I_th element OR not?
 * => KNAPSACK!
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

        vector<vector<bool>> memo(nums.size(), vector<bool>(target + 1, false));

        for (int i = 0; i < memo.size(); i++)
            memo[i][0] = true;
        if (nums[0] >= 0 && nums[0] < target + 1)
            memo[0][nums[0]] = true;

        // T(sum,i) = T(sum - arr[i], i-1) || T(sum, i-1)

        for (int i = 1; i < memo.size(); i++)
        {
            for (int curTarget = 0; curTarget < target + 1; curTarget++)
            {
                memo[i][curTarget] = memo[i - 1][curTarget];
                if (curTarget - nums[i] < target + 1 && curTarget - nums[i] >= 0 && memo[i - 1][curTarget - nums[i]])
                {
                    memo[i][curTarget] = true;
                }
            }
            if (memo[i][target])
                return true;
        }

        return false;
    }
};

/**
 * @brief Brute force Backtracking approach -TLE
 *
 */

bool backTrack(int target, vector<int> &nums, int curSum, int curIndex)
{
    if (target == curSum)
        return true;
    if (curSum > target)
        return false;

    bool res = false;
    for (int i = curIndex; i < nums.size(); i++)
    {
        curSum += nums[i];
        res = backTrack(target, nums, curSum, i + 1);
        if (res)
            return res;
        curSum -= nums[i];
    }
    return res;
}
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

    return backTrack(target, nums, 0, 0);
}