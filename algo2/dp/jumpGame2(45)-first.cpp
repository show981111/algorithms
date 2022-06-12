/**
 * @brief Traditional Way of Memoization
 * Memo : the minimum number of steps to reach that index
 * Time : O(sum of nums)
 * Space : O(n)
 *
 * Think : We do not need to fill the min for all steps
 * All we need to know is min for LastIndex.
 * Also, we know that from "i" to that specifc "to", the number of step is all the same.
 */

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        vector<int> memo(nums.size());
        int N = nums.size();

        for (int i = 0; i < N; i++)
        {
            int to = min(N - 1, nums[i] + i);
            for (int j = i + 1; j <= to; j++) // fill memo
                memo[j] = memo[j] == 0 ? memo[i] + 1 : min(memo[j], memo[i] + 1);
        }
        return *memo.rbegin();
    }
};