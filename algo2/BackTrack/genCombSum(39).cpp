/**
 * @brief
 * BackTracking
 * => decide where to stop(push to the res array)
 *  and how to proceed!(recursive part)
 *
 * Pattern :
 * For(choices I have in current step)
 *      do something -> call recursive(go to next step) -> roll back
 */

class Solution
{
public:
    void genComb(vector<int> &candidates, vector<int> &cur, int curSum, int target, int curIndex, vector<vector<int>> &res)
    {
        if (curSum == target)
        {
            res.push_back(cur);
            return;
        }
        if (curSum > target)
            return;
        for (int i = curIndex; i < candidates.size(); i++)
        {
            int newSum = curSum + candidates[i];
            if (newSum <= target)
            {
                cur.push_back(candidates[i]);
                genComb(candidates, cur, newSum, target, i, res); // crucial part is putting i not i + 1
                cur.pop_back();
            }
        }
        /**
         * @brief By putting i instead of i + 1, we can choose current element unlimited times!
         * Also, we can exclude items we ve already chosen!
         */
        /**
         * First Trial
         * Just generate comb from zero index cause I thought it is necessary
         * because we can pick any elem for unlimited times.
         * => this cause redundancy, it creates permutations
         * ex) {2,2,3}, {2,3,2}, {3,2,2} which is obvious because
         * we have all choices(we did not care what we have already chosen)
        for (int i = 0; i < candidates.size(); i++)
        {
            int newSum = curSum + candidates[i];
            if (newSum <= target)
            {
                cur.push_back(candidates[i]);
                genComb(candidates, cur, newSum, target, res);
                cur.pop_back();
            }
        }
        */
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> res;
        vector<int> path;
        genComb(candidates, path, 0, target, 0, res);
        return res;
    }
};