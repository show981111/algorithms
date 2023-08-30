/**
 * @brief Unique elements with additional contraints(the size of combination)
 *
 */

class Solution
{
public:
    void backTrack(vector<vector<int>> &ans, vector<int> &cand, vector<int> &cur, int curIndex, int curSum, int k, int target)
    {
        if (cur.size() == k && curSum == target)
        {
            ans.push_back(cur);
            return;
        }
        if (cur.size() >= k || curSum > target) // cur.size() == k but curSum is not eqaul to target.. out!
            return;

        for (int i = curIndex; i < cand.size(); i++)
        {
            int nextSum = curSum + cand[i];
            if (nextSum <= target)
            {
                cur.push_back(cand[i]);
                backTrack(ans, cand, cur, i + 1, nextSum, k, target);
                cur.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<int> cand = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        if (n < 10)
        {
            auto newEnd = remove_if(cand.begin(), cand.end(), [n](const int &x)
                                    { return x > n; });
            cand.erase(newEnd, cand.end());
        }
        vector<vector<int>> ans;
        vector<int> cur;
        backTrack(ans, cand, cur, 0, 0, k, n);
        return ans;
    }
};