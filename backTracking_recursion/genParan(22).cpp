class Solution
{
public:
    void solve(vector<string> &res, string &path, int open, int close, int n)
    {
        if (path.size() == 2 * n)
        {
            res.push_back(path);
            return;
        }
        if (open >= close)
        {
            if (open < n) // open par is max n amount
            {
                path.push_back('(');
                solve(res, path, open + 1, close, n);
                path.pop_back();
            }
            path.push_back(')'); // we can close whenever it is already opened
            solve(res, path, open, close + 1, n);
            path.pop_back();
        } // if close > open, invalid
    }
    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        string path = "";
        solve(res, path, 0, 0, n);
        return res;
    }
};