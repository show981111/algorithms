/**
 * @brief How to skip redundant values?
 * So the key is do not permute same values
 * Using a map, we iterate only unique elements!
 *
 * Flow is all the same.
 * Just iterate map instead of vector.
 * subtract frequency and add number to the path,
 * call recursive
 * then add freq and pop back the path(return to original)
 */

class Solution
{
public:
    void genPerms(unordered_map<int, int> &mp, vector<int> &path, int permSize, vector<vector<int>> &res)
    {
        if (path.size() == permSize)
        {
            res.push_back(path);
            return;
        }
        for (auto item : mp)
        {
            if (item.second > 0)
            {
                path.push_back(item.first);
                mp[item.first]--;
                genPerms(mp, path, permSize, res);
                mp[item.first]++;
                path.pop_back();
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<vector<int>> res;
        unordered_map<int, int> mp;
        for (auto i : nums)
            mp[i]++;
        vector<int> path;
        genPerms(mp, path, nums.size(), res);
        return res;
    }
};