class Solution
{
public:
    void genParan(int n, int left, int right, string &path, vector<string> &ans)
    {
        if (path.length() == 2 * n)
        {
            ans.push_back(path);
            return;
        }

        if (left < n) // First, place open paranthesis first!
        {
            left++;
            path.push_back('(');
            genParan(n, left, right, path, ans);
            left--;
            path.pop_back();
        }
        if (right < left) // Then, if there is more open parantehsis, then close it!
        {
            right++;
            path.push_back(')');
            genParan(n, left, right, path, ans);
            right--;
            path.pop_back();
        }
    }

    vector<string> generateParenthesis(int n)
    {
        vector<string> ans;
        string path = "";
        genParan(n, 0, 0, path, ans);
        return ans;
    }
};