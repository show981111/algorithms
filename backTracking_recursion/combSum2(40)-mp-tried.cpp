class Solution
{
public:
    void genUniqueComb(unordered_map<int, int> &mp, vector<int> &cur, int curSum, int target, vector<vector<int>> &res)
    {
        if (curSum == target)
        {
            res.push_back(cur);
            return;
        }
        if (curSum > target)
            return;

        for (auto &it : mp)
        {
            if (it.second > 0)
            {
                int newSum = curSum + it.first;
                if (newSum <= target)
                {
                    cur.push_back(it.first);
                    mp[it.first]--;
                    genUniqueComb(mp, cur, newSum, target, res);
                    cur.pop_back();
                    mp[it.first]++;
                }
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        unordered_map<int, int> mp;
        vector<int> cur;
        vector<vector<int>> res;
        for (auto i : candidates)
            mp[i]++;
        genUniqueComb(mp, cur, 0, target, res);
        return res;
    }
};