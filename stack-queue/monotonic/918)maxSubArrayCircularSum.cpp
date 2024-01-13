/**
 * Monotonic Deque
 *
 * Max difference among all pairs in the array!
 *
 * https://leetcode.com/problems/maximum-sum-circular-subarray/description/
 */

class Solution
{
public:
    typedef pair<int, int> Val; // value, index

    int maxSubarraySumCircular(vector<int> &nums)
    {
        int len = nums.size();
        vector<int> prefix(2 * len);
        deque<Val> incDeq;
        prefix[0] = nums[0];
        for (int i = 1; i < 2 * len; i++)
        {
            prefix[i] = nums[i % len] + prefix[i - 1];
        }
        int maxSum = nums[0];

        int left = 0, right = 0;

        while (right < 2 * len)
        {
            while (!incDeq.empty() && right - incDeq.front().second > len)
            {
                incDeq.pop_front(); // pop if it makes a subarray bigger than "len"
            }
            if (!incDeq.empty() && right - incDeq.front().second <= len)
            {
                maxSum = max(maxSum, prefix[right] - incDeq.front().first);
                // compute possible maxSum
            }
            while (!incDeq.empty() && incDeq.back().first > prefix[right])
            {
                incDeq.pop_back();
                // increasing deque invariant (elements are ascending ordered). pop elems that are bigger than current prefix
            }
            if (right < len)
                maxSum = max(maxSum, prefix[right]);
            incDeq.push_back({prefix[right], right});
            right++;
        }

        return maxSum;
    }
};