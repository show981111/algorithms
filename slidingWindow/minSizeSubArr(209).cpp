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