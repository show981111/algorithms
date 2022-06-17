/**
 * @brief Greedy + binary Search
 * https://leetcode.com/problems/longest-increasing-subsequence/discuss/1326308/C%2B%2BPython-DP-Binary-Search-BIT-Solutions-Picture-explain-O(NlogN)
 * 
 */

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ans;
        ans.reserve(nums.size());

        for (int i = 0; i < nums.size(); i++)
        {
            if (ans.empty() || *ans.rbegin() < nums[i])
            {
                ans.push_back(nums[i]);
            }
            else
            {
                auto it = lower_bound(ans.begin(), ans.end(), nums[i]);
                // lower_bound(begin iter, end iter, x) : it found the smallest number >= x
                // Returns an iterator pointing to the first element in the range [first,last) which does not compare less(greater or equal) than val.
                // upper_bound returns smallest number "GREATER" than x(not equal!)
                // apply this on sorted array, Log(N) time
                *it = nums[i];
            }
        }
        return ans.size();
    }
};