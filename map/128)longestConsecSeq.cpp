/**
 * How to make it O(N)?
 *
 * Need to prevent redundant traverse.
 * Find the starting point of the sequence by searching num - 1!
 * If we have num - 1, that means num - 1 is the starting so skip.
 */

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> st(nums.begin(), nums.end());
        int longestDist = 0;
        for (int num : nums)
        {
            if (st.count(num - 1) > 0)
                continue; // not a start of the sequence

            int dist = 1; // starting from 1 since num itself has length 1
            while (st.count(num + 1) > 0)
            {
                dist++;
                num++;
            }

            longestDist = max(longestDist, dist);
        }
        return longestDist;
    }
};