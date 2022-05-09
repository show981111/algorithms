class Solution
{
public:
    vector<vector<int> > res;
    void genPerms(int n, vector<int> &path)
    {
        if (path.size() == n)
        {
            res.push_back(path);
            return;
        }
        for (int i = n; i < path.size(); i++)
        {
            swap(path[i], path[n]);
            genPerms(n + 1, path);
            swap(path[i], path[n]);
        }
    }
    vector<vector<int> > permute(vector<int> &nums)
    {
        genPerms(0, nums);
        return res;
    }
};