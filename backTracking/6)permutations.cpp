/**
 * @brief Permutation
 * Unlike Combination We use SWAP!
 * Idea here is 0 ~ curIndex is permuted part.
 * We should permute from curIndex~ end.
 * WE should backTrack from curIndex + 1 not i + 1 because,
 * the only part it is permuted is ~ curIndex!
 *
 */

class Solution
{
public:
    void genPerms(vector<vector<int>> &ans, vector<int> &path, int curIndex)
    {
        if (curIndex == path.size())
        {
            ans.push_back(path);
            return;
        }

        for (int i = curIndex; i < path.size(); i++)
        {
            swap(path[i], path[curIndex]);
            genPerms(ans, path, curIndex + 1); // genPerms(ans,path,i+1);
            swap(path[i], path[curIndex]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> ans;
        genPerms(ans, nums, 0);
        return ans;
    }
};