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
 * @brief Other(slight application of combination)
 * subsets == getting all combinations(nCk, k = 0 ~ n)
 * So if we should push back cur, when cur.size() == 0,1,2,3,...,n
 * This means we can just remove the if statement!
 */
class Solution
{
public:
    void backTrack(vector<int> &nums, vector<vector<int>> &res, vector<int> &cur, int curIndex)
    {
        // if(cur.size() == 2){ if we uncomment this part, it becomes genComb!
        res.push_back(cur); // wihtout cur element!
        //     return;
        // }

        for (int i = curIndex; i < nums.size(); i++)
        {
            cur.push_back(nums[i]);
            backTrack(nums, res, cur, i + 1);
            cur.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> cur;
        backTrack(nums, res, cur, 0);
        return res;
    }
};