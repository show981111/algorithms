/**
 * @brief
 *
 */
class Solution
{
public:
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {
        // if num[end] == 0; add T(N-1) + current cnt (goal could be 0!)
        // if num[end] == 1; add it to curSum, if curSUm == goal, shrink right, add cnt
        // No impact if I start from shrunken right. Why? if we move "right" back, then
        // it will include 1 that we passed while shrinking, and it will exceed the goal.
        // So, no way we can make a subarray with previous elems of "right"
        int cnt = 0;
        int start = 0, end = 0;
        int prevCount = 0;
        int curSum = 0;

        while (end < nums.size())
        {
            int tmpCnt = cnt;
            if (nums[end++] == 0)
            {
                cnt += prevCount;
            }
            else
            {
                curSum++;
            }
            // Shrink Window. <- when we need to shrink it?
            // curSum >= goal. (if curSum > goal, we need to shrink to take out 1s)
            // if curSum == goal, we need to shrink so that we can count #subarray that
            // suffices goal.
            while (start < end && curSum >= goal)
            {
                if (curSum == goal)
                    cnt++;
                curSum -= nums[start++];
            }
            prevCount = cnt - tmpCnt;
            // cout << prevCount << " ";
        }

        return cnt;
    }
};