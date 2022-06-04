/**
 * @brief How to skip redundant values?
 * So the key is do not permute same values
 * If we pass nums by reference, then due to additional swapping, there must be
 * redundant values
 * So we should keep the original one and swapping different values
 *
 * First we sort the array so that the redundant values must stick together.
 * Then pass nums by value
 *
 * In this case we do not roll back to original after we call genPerms.
 * We just use that sequence directly to avoid redundanct due to second swapping
 */

class Solution
{
public:
    void genPerms(vector<int> nums, int permLength, vector<vector<int>> &res)
    {
        if (permLength == nums.size() - 1)
        {
            res.push_back(nums);
            return;
        }

        for (int i = permLength; i < nums.size(); i++)
        {
            if (i > permLength && nums[permLength] == nums[i])
            {
                continue;
            }
            swap(nums[permLength], nums[i]);
            genPerms(nums, permLength + 1, res); // 1 1 2 2
            // swap(nums[permLength], nums[i]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end()); // 1 1 2 2
        genPerms(nums, 0, res);
        return res;
    }
};