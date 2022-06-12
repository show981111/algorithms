class Solution
{
public:
    int rob(vector<int> &nums)
    {
        // vector<int> memo(nums.size());
        if (nums.size() == 0)
            return 0;
        else if (nums.size() == 1)
            return nums[0];
        else if (nums.size() == 2)
            return max(nums[0], nums[1]);
        else if (nums.size() == 3) // 1 > n - 2
            return max(nums[1], max(nums[0], nums[2]));
        // first case : 0 ~ n-1
        int first = nums[0];
        int second = max(nums[0], nums[1]);
        int res;
        for (int i = 2; i < nums.size() - 1; i++)
        {
            res = max(first + nums[i], second);
            first = second;
            second = res;
        }
        int from0 = res;
        // cout << from0 << " ";
        //  second case : 1 ~ n - 2 + nums[n]
        first = nums[1];
        second = max(nums[1], nums[2]);
        res = first;
        // cout << res;
        for (int i = 3; i < nums.size() - 2; i++)
        {
            res = max(first + nums[i], second);
            first = second;
            second = res;
        }
        return max(from0, res + *nums.rbegin());
    }
};