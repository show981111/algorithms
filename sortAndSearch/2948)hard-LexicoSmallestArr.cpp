/**
 * https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/description/
 */

class Solution
{
public:
    vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit)
    {
        vector<pair<int, int>> sorted;
        for (int i = 0; i < nums.size(); i++)
        {
            sorted.push_back({nums[i], i});
        }
        sort(sorted.begin(), sorted.end(), [](pair<int, int> &a, pair<int, int> &b)
             { return a.first > b.first; });
        vector<vector<int>> groupIndices;    // group of indices
        vector<int> groupIndex(nums.size()); // original index -> group Index
        for (int i = 0; i < sorted.size();)
        {
            vector<int> group;
            int val = sorted[i].first;
            group.push_back(sorted[i].second);
            int j = i + 1;
            for (j = i; j < sorted.size(); j++)
            {
                if (val - sorted[j].first <= limit)
                {
                    group.push_back(sorted[j].second);
                    val = sorted[j].first;
                    groupIndex[sorted[j].second] = groupIndices.size();
                }
                else
                {
                    break;
                }
            }
            groupIndices.emplace_back(group);
            i = j;
        }

        vector<int> answerIndices(nums.size());
        for (int i = 0; i < nums.size(); i++)
        {
            answerIndices[i] = groupIndices[groupIndex[i]].back();
            groupIndices[groupIndex[i]].pop_back();
        }
        vector<int> ans(nums.size());
        for (int i = 0; i < answerIndices.size(); i++)
        {
            ans[i] = nums[answerIndices[i]];
        }
        return ans;
    }
};