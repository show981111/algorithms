/**
 * @brief
 * Sliding window is tricky to decide when we should stop shrinking.
 * In this case, should we stop to keep the minimum size window that the sum == goal?
 * or should we stop to keep the window largest size that sum < goal
 *
 * This case, later is much easier to compute, since we can avoid the duplicate counts.
 * EX)
 * [0,<1,0,1,0>] target = 2
 * If the right is 0, we concat 0 to previous subarrays to make the goal.
 * So we already counted <1,0,1,0>
 *
 * Now, when we shrink window, we double count <1,0,1,0> since it is target sum!
 *
 * So invariant of the window => largest size window that sum < goal ends at "END"
 * This way, we count everything we need in that window, but at the same time no duplicate counts
 * since the target sum will be smaller than the goal when we include a new elem.
 * (target sum can only be achieved by including a new elem)
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
            // Now curSum < goal or start == end.
            // so only way to achieve the goal is by adding a new elem =>
            //      can prevent duplicate counting when shrinking the window of next elem!
            prevCount = cnt - tmpCnt;
            // cout << prevCount << " ";
        }

        return cnt;
    }
};