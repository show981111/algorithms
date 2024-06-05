/**
 * @brief Populate answer while building the path.
 * the other version is populating answer after we reach the answer
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
            curPath.push_back(nums[i]);       // include current elem
            genSubsets(nums, i + 1, curPath); // gen subset with other
            curPath.pop_back();               // pop
        }
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<int> curPath;
        genSubsets(nums, 0, curPath);
        return res;
    }
};