/**
 * @brief Linear Sliding Window
 *
 * Moving sliding window like this!
 * curSum += nums[right++]
 * curSum -= nums[left++]
 */

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int start = 0, end = 0;
        int minLength = nums.size() + 1;
        int curSum = 0;

        while (end < nums.size())
        {
            curSum += nums[end];

            while (curSum >= target)
            { // MUST STOP!
                minLength = min(minLength, end - start + 1);
                curSum -= nums[start++];
            }
            end++;
        }

        return minLength == nums.size() + 1 ? 0 : minLength;
    }
};

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int N = nums.size();
        int start = 0;
        int minLength = N + 1;
        int curSum = 0;
        for (int end = 0; end < N; end++)
        {
            if (nums[end] >= target)
                return 1;
            curSum += nums[end];
            while (start <= end && curSum - nums[start] >= target)
            {
                curSum -= nums[start++];
            }
            // cout << curSum << " => " << start << " " << end << endl;
            if (curSum >= target)
                minLength = minLength > (end - start + 1) ? (end - start + 1) : minLength;
        }
        return minLength == N + 1 ? 0 : minLength;
    }
};