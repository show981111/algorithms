/**
 * @brief
 * The problem was we are picking same elements multiple times (combSum2 problem)
 * However, we still can pick the same element as many times as they exist.
 * Thus, all we need to do is just skip the same element.
 * by putting i > curIndex, we can count that redundant element exactly as many as it exist
 * (존재하는만큼만 픽가능)
 * The reason why there are redundant elements in the result is
 * [10,1(A),2,7,6,1(B),5] , target = 8
 * My out : [[1,2,5],[1,7],[1,6,1],[2,6],[2,1,5],[7,1]]
 * Answer : [[1,1,6],[1,2,5],[1,7],[2,6]]
 * [1(A), 1(B), 2, 5, 6, 7, 10]
 * First : pick 1(A), then in next step(recursive call) curIndex is 1, it picks 2 so it makes [1(A),2,5]
 * Second : Then, it returns to 1(A). it pops back 1(A). Then it picks 1(B).
 * call recursive fuction, in curIndex 1, it picks 2 again, then it makes [1(B),2,5]
 * Thus it makes redundant elements because it couldn't skip the same elements.
 * Thus, if we skip the same element, then we can avoid picking the same element in the same step(same curIndex)
 */

class Solution
{
public:
    void genUniqueComb(vector<int> &cand, vector<int> &cur, int curSum, int curIndex, int target, vector<vector<int>> &res)
    {
        if (curSum == target)
        {
            res.push_back(cur);
            return;
        }
        if (curSum > target)
            return;

        for (int i = curIndex; i < cand.size(); i++)
        {
            if (i > curIndex && cand[i - 1] == cand[i])
                continue;
            int newSum = curSum + cand[i];
            if (newSum <= target)
            {
                cur.push_back(cand[i]);
                genUniqueComb(cand, cur, newSum, i + 1, target, res);
                cur.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        unordered_map<int, int> mp;
        vector<int> cur;
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
        genUniqueComb(candidates, cur, 0, 0, target, res);
        return res;
    }
};