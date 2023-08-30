/**
 * @brief Combination with non unique elements
 * We have duplicate elements in candidate pool ex)[1,2,3,3,3,4]
 * How do we extract a unique combination?
 * ex)[1,3(index 2),4] == [1,3(index 3),4]
 * But at the same time, we can use those duplicate elements as many as they exists.
 * ex) [3,3,3] (o), [3,3,3,3](x)
 *
 * So the key is 1) remove duplicate combination 2) only use as many as they exsits.
 *
 * For 1) we can SORT and skip the same elements.
 * However, we should not skip current Index because we should be able to choose
 * as many as they exists. If we just skip the same element, then [1,2,3,3,3,4] will
 * be same as [1,2,3,4] (we cannot select the same element multiple times even though
 * there are multiple elements)
 *
 * For 2) we can pass i+1 to backTrack, so that it won't be able to pick the same
 * element again
 *
 * We do not need to use a map here.
 * Why? we can fulfill both 1) and 2) by sorting.
 *
 */

class Solution
{
public:
    void backTrack(vector<vector<int>> &ans, vector<int> &cand, vector<int> &cur, int curSum, int curIndex, int target)
    {
        if (curSum > target)
            return;
        if (curSum == target)
        {
            ans.push_back(cur);
            return;
        }
        // if(curIndex == cand.size())
        //     return;

        for (int i = curIndex; i < cand.size(); i++)
        {
            if (i != curIndex && cand[i] == cand[i - 1])
                continue;
            int nextSum = curSum + cand[i];
            if (nextSum <= target)
            {
                cur.push_back(cand[i]);
                backTrack(ans, cand, cur, nextSum, i + 1, target);
                cur.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        auto newEnd = remove_if(candidates.begin(), candidates.end(), [target](const int &x)
                                { return x > target; });
        candidates.erase(newEnd, candidates.end());
        vector<vector<int>> ans;
        vector<int> cur;
        backTrack(ans, candidates, cur, 0, 0, target);
        return ans;
    }
};