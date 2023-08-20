/**
 * @brief Bottom up DP
 * Consider the relationship between including current term and not.
 * EX) 1 2 3 4 5
 *
 * (1 2 3) (1 2 3 4) (1 2 3 4 5)
 *         (2 3 4)   (2 3 4 5)
 *                   (3 4 5)
 *
 * So T(n) = T(n-1) + [T(n-1) - T(n-2)] + 1(new subArray with current elem ex)3,4,5 )
 *                     Difference(where we can add current number and make a new one ex)5 )
 */

class Solution
{
public:
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        if (nums.size() < 3)
            return 0;
        vector<int> memo(nums.size());
        int N = nums.size();
        for (int i = 2; i < N; i++)
        {
            int prevDiff = nums[i - 1] - nums[i - 2];
            int curDiff = nums[i] - nums[i - 1];

            if (prevDiff == curDiff)
                memo[i] = 2 * memo[i - 1] - memo[i - 2] + 1;
            else
                memo[i] = memo[i - 1];
        }
        return memo[N - 1];
    }
};

/**
 * @brief Bottom-up O(1) Space
 *
 */

class Solution
{
public:
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        if (nums.size() < 3)
            return 0;
        // vector<int> memo(nums.size());
        int fir = 0, sec = 0, thir = 0;
        int N = nums.size();
        for (int i = 2; i < N; i++)
        {
            int prevDiff = nums[i - 1] - nums[i - 2];
            int curDiff = nums[i] - nums[i - 1];

            if (prevDiff == curDiff)
                thir = 2 * sec - fir + 1;
            fir = sec;
            sec = thir;
        }
        return thir;
    }
};