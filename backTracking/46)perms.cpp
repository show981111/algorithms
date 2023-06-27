/**
 * @brief Recursive structure!
 *
 */

class Solution
{
public:
    void genPerm(vector<int> &nums, int index, vector<vector<int>> &res)
    {
        if (index >= nums.size())
        {
            res.push_back(nums);
            return;
        }

        for (int i = index; i < nums.size(); i++) // Insert == swap nums[index] to every possible positions!
        {
            swap(nums[i], nums[index]);
            genPerm(nums, index + 1, res); // Then go get T(N+1), cuz T(N) is fixed now!
            swap(nums[i], nums[index]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        /*
        T([0:n] perms) = For each position of T([0:n-1]), insert a[n]!
        EX) 1,2,3
            T(n-1) = [1,2] & [2,1]
            [3,1,2] / [1,3,2] / [1,2,3] (insert 3 to [1,2] to all possible pos)
            [3,2,1] / [2,3,1] / [2,1,3]
        */
        vector<vector<int>> res;
        genPerm(nums, 0, res);
        return res;
    }
};