/*
Thought Process
    Subset decision tree => 0/x
    [1,5,11,5] => GOAL 11
    1(0) - 5(0) - 11(0) X
                - 5(0) == 11 => CHECK SUM OF OTHER ELEMS
         - 5(x) - 11(o) x
                - 5(o)
    [1,2,3,5] => GOAL 11/2
    1(o) -> 2(o) -> 3(o)
    Redundant. When we check if subset(1,2,3) works, we can get that {5} is not working too. But, later we calculate {5} is possible again.
    [- n -] canPartition. hb [- n -] + [A]
============= IDENTIFYING INVARIANT
    IF WE FIND THE SUBSET THAT SUMS UP TO TOTAL/2, then answer is true.
    (We know the total sum is TOTAL, if we make half, the other must be half)
    Now question is, how to build a subset that sums up to total/2?
    KNAPSACK?
    T(i, v) = can make a sum of v using 0 ~ i_th items
    T(i, v) = T(i-1, v - arr[i]) || T(i-1, v) => (Use or Not use)
    BASE CASE: We can always make value 0 by not picking anything
        0 1 2 3 4 5
      0 T F F F F F
      1 T
*/

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (int num : nums)
            sum += num;
        if (sum % 2 == 1)
            return false;
        int target = sum / 2;
        vector<vector<bool>> memo(nums.size() + 1, vector<bool>(target + 1, false));
        for (int i = 0; i < memo.size(); i++)
            memo[i][0] = true;

        for (int i = 1; i < memo.size(); i++)
        {
            for (int val = 1; val <= target; val++)
            {
                if (val - nums[i - 1] >= 0)
                {
                    memo[i][val] = memo[i - 1][val] || memo[i - 1][val - nums[i - 1]];
                }
                else
                {
                    memo[i][val] = memo[i - 1][val];
                }
            }
        }
        return memo.back().back();
    }
};