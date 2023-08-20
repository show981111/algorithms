/**
 * @brief Permutation
 * Unlike Combination We use SWAP!
 * Idea here is 0 ~ curIndex is permuted part.
 * We should permute from curIndex~ end.
 * WE should backTrack from curIndex + 1 not i + 1 because,
 * the only part it is permuted is ~ curIndex!
 *
 * Basic idea is,
 * T(N) = For every position in T(N-1): push A[1]
 * EX) 1,2,3
 * T(n-1) = [1,2] & [2,1]
 * [3,1,2] / [1,3,2] / [1,2,3] (insert 3 to [_ 1 _ 2 _] to all possible pos)
 * [3,2,1] / [2,3,1] / [2,1,3]
 *  OR
 *
 * T(N) = A[1] + T(N- A[1]) U A[2] + T(N- A[2]) ...
 *      => this is why we swap A[curIndex] with A[curIndex + 1 ~ N], Until curIndex, it is like fixed
 *          (A[1] part) after addition part T(N-A[1]) is the genPerm recursive call!
 *          ex) 1,2,3,4,5 curIndex = 2
 *          swap(3,3) (A[2] + T(N - A[:2]))-> swap(4,4) -> swap(5,5) => push 1,2,3,4,5
 *                                            swap(4,5)([5 fixed] + T(1,2,3,4)) -> swap(4,4) => push 1,2,3,5,4
 *          swap(3,4) ([4 fixed] + T(1,2,3,5)) but after curindex is fixed, so its like T(3,5) ...
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

/**
 * @brief Another solution using push_back
 *
 * Simple DFS.
 * From A[1] ~ A[N], sequentially pick something we haven picked!
 * ex) pick A[1] -> A[2] -> A[3] ... then come back, pick A[2] -> A[1] -> A[3] -> ...
 * Just like DFS, since we need which elem we picked, we need used(=visited) array
 */

class Solution
{
public:
    void genPerm(vector<int> &nums, vector<vector<int>> &res, vector<int> &path, vector<bool> &used)
    {
        if (path.size() == nums.size())
        {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i])
                continue;
            path.push_back(nums[i]);
            used[i] = true;
            genPerm(nums, res, path, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        genPerm(nums, res, path, used);
        return res;
    }
};

/**
 * @brief Easiest way of thinking
 * From T(n-1), who can we make T(N)?
 * build from base
 *
 * T(1) = {1}
 * T(2) = {1,2}, {2,1}
 * T(3) = {3,1,2}, {1,3,2}, {1,2,3} // {3,2,1}, {2,3,1}, {2,1,3}
 * So for every possible position from T(N-1), we insert nums[n]!
 *
 */

class Solution
{
public:
    vector<vector<int>> genPerm(vector<int> &nums, int curIndex)
    {
        vector<vector<int>> res;
        if (curIndex == 0)
        {
            res.push_back({nums[0]});
            return res;
        }
        int num = nums[curIndex];
        vector<vector<int>> prevPerms = genPerm(nums, curIndex - 1);
        for (auto &perm : prevPerms)
        {
            for (int i = 0; i < perm.size(); i++)
            {
                vector<int> temp = perm;
                temp.insert(temp.begin() + i, num);
                res.push_back(temp);
            }
            perm.push_back(num);
            // For all possible position, insert num!
            res.push_back(perm);
        }

        return res;
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        return genPerm(nums, nums.size() - 1);
    }
};

/**
 * @brief Build from all perms of length N-1
 * P(SET) = all permutations of SET
 * ex)
 * P({1}) = {1},
 *
 * P({1,2}) = ({1} + P{2}) + ({2} + P{1}) = {1,2}, {2,1}
 * P({1,3}) = ({1} + P{3}) + ({3} + P{1}) = {1,3}, {3,1}
 * P({2,3}) = ({2} + P{3}) + ({3} + P{2}) = {2,3}, {3,2}
 *
 * P{1,2,3} = ({1} + P{2,3})(SWAP{1,1}) + ({2} + P{1,3})(SWAP{1,2}) + ({3} + P{1,2})(SWAP{1,3})
 *
 * SWAP{1,1} => {1} + P{2,3}
 * SWAP{1,2} => {1,2,3} => {2,1,3}, then PERM({1,3}) so {2} + PERM{1,3}
 * SWAP{1,3} => {3,2,1} => then perm({2,1}) so {3} + PERM{2,1}
 *
 * Build permutation without i_th elem, and add that item back!
 */

class Solution
{
public:
    vector<vector<int>> genPerm(vector<int> &nums)
    {
        vector<vector<int>> res;
        if (nums.size() == 0)
        {
            res.push_back({});
            return res;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            int item = nums[i];
            nums.erase(nums.begin() + i);             // delete that num
            vector<vector<int>> prev = genPerm(nums); // create perm without it!
            nums.insert(nums.begin() + i, item);      // then add that num back!

            for (auto &perm : prev)
            {
                perm.push_back(item);
                res.push_back(move(perm));
            }
        }

        return res;
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        return genPerm(nums);
    }
};