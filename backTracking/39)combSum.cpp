/**
 * @brief Combination, but we can pick each element as many as we want
 * However, we don't allow redundant combination ex) 2 2 3 == 2 3 2 == 3 2 2
 * Fortunately, each element is unique.
 *
 * Now traditional way of getting a combination does not allow picking the same
 * element again... what should we do?
 *
 * For loop inside backTrack
 * 1) starting from i = 0 everytime ex) for(int i = 0; i < cand.size; i++)
 * it creates redundant combination
 * ex) [2 3 4 5]
 * we pick 2, 3, 4 / 3 2 4 / 4 2 3 ..
 * Since we start from 0 index every time we can pick everyting again and again
 *
 * 2) starting from i = curIndex, but passing curIndex to next backTrack not curIndex + 1
 * ## backTrack(ans, candidates, cur, i, curSum + candidates[i], target);
 * Key differnece... we can only pick from [curIndex:] but we can pick
 * each elem infinite time because we start from curIndex at next backTracking!
 *
 */

class Solution
{
public:
    void backTrack(vector<vector<int>> &ans, vector<int> &candidates, vector<int> &cur, int curIndex, int curSum, int target)
    {
        if (curSum > target)
            return;
        if (curSum == target)
        {
            ans.push_back(cur);
            return;
        }
        if (curIndex == candidates.size())
            return;

        for (int i = curIndex; i < candidates.size(); i++)
        {
            cur.push_back(candidates[i]);
            backTrack(ans, candidates, cur, i, curSum + candidates[i], target);
            cur.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> cur;
        backTrack(ans, candidates, cur, 0, 0, target);
        return ans;
    }
};