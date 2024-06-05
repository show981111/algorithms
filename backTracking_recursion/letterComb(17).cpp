/**
 * @brief BackTrack == DFS
 * Just think permuting the solution as a finding the path to the solution!
 * DFS!
 */

class Solution
{
public:
    void dfs(vector<string> &res, vector<string> &digitToStrMap, string &path, string &digits, int curStep)
    {
        if (curStep == digits.size())
        {
            res.push_back(path);
            return;
        }
        int curNum = digits[curStep] - '0';
        for (int i = 0; i < digitToStrMap[curNum].size(); i++)
        {
            path.push_back(digitToStrMap[curNum][i]);
            dfs(res, digitToStrMap, path, digits, curStep + 1);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits)
    {
        vector<string> res;
        if (digits == "")
            return res;
        string path = "";
        vector<string> digitToStrMap = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        dfs(res, digitToStrMap, path, digits, 0);
        return res;
    }
};