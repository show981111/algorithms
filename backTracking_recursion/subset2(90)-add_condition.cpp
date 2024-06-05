class Solution
{
public:
    vector<vector<int>> res;

    void genSubsets(vector<int> &nums, int cur, vector<int> &curPath)
    {
        if (cur == (int)nums.size())
        {
            if (find(res.begin(), res.end(), curPath) != res.end()) // already in the set, skip
                return;
            res.push_back(curPath);
            return;
        }
        genSubsets(nums, cur + 1, curPath); // skip current elem
        curPath.push_back(nums[cur]);       // include current elem
        genSubsets(nums, cur + 1, curPath); // gen subset with cur elem
        curPath.pop_back();                 // pop
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end()); // sort the array so that there is no redundancy
        vector<int> curPath;
        genSubsets(nums, 0, curPath);
        return res;
    }
};