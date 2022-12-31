/**
 * @brief Redundant subset
 * {1,2,1} => {1} = {1} since the previous solution regards all elements as unique
 * {1,2} = {2,1}
 *
 */

class Solution
{
public:
    vector<vector<int>> res;

    void genSubsets(vector<int> &nums, int cur, vector<int> &curPath)
    {
        res.push_back(curPath);

        for (int i = cur; i < nums.size(); i++)
        {
            if (i > cur && nums[i] == nums[i - 1]) // skip redundant. just add current one
                continue;
            curPath.push_back(nums[i]);       // include current elem
            genSubsets(nums, i + 1, curPath); // gen subset with cur elem
            curPath.pop_back();               // pop
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<int> curPath;
        genSubsets(nums, 0, curPath);
        return res;
    }
};