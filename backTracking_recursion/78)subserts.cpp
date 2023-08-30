/**
 * @brief Subset => 0/1 problem
 * Two possibility for all elem.
 * Include this elem or not!
 */

class Solution
{
public:
    void backTrack(vector<int> &nums, vector<vector<int>> &res, vector<int> &cur, int curIndex)
    {
        if (curIndex == nums.size())
        {
            res.push_back(cur);
            return;
        }

        cur.push_back(nums[curIndex]);
        backTrack(nums, res, cur, curIndex + 1); // including current elem
        cur.pop_back();
        backTrack(nums, res, cur, curIndex + 1); // except current elem
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> cur;
        backTrack(nums, res, cur, 0);
        return res;
    }
};

/**
 * @brief Recursive Call
 * SubSet[~i] = Subset[~i-1] U {Subset[~i-1] + nums[i]} (without, and with current elem from
 *                                                          previous subsets)
 */

class Solution
{
public:
    void subset(vector<vector<int>> &res, vector<int> &nums, vector<int> &cur, int index)
    {
        // cur is subset[~i-1] (subset from previous call is stored in cur)
        res.push_back(cur);

        for (int i = index; i < nums.size(); i++)
        {
            cur.push_back(nums[i]);        // subset[~i-1] U nums[i]
            subset(res, nums, cur, i + 1); // pass i+1 to prevent redundant elem
                                           // since we chose elem till i, go to i+1
            cur.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> cur;
        // Subset[~i] = {subset[~i-1] + nums[i]} U subset[~i-1]

        subset(res, nums, cur, 0);
        return res;
    }
};
