/**
 * @brief Problem of just generating a combination
 * [10,1(A),2,7,6,1(B),5] , target = 8
 * My out : [[1,2,5],[1,7],[1,6,1],[2,6],[2,1,5],[7,1]]
 * Answer : [[1,1,6],[1,2,5],[1,7],[2,6]]
 * Since this combination consider all of them as just a unique value,
 * it shows two [1(A),2,5], [1(B),2,5]
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

        genUniqueComb(candidates, cur, 0, 0, target, res);
        return res;
    }
};