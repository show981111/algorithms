/**
 * BackTrack think it as a Decision Graph!
 * Bascially just iterating all possible nodes in the graph!
 */

class Solution
{
public:
    void dfs(vector<string> &res, vector<string> &mp, string &digits, int curIndex, string &curLetterComb)
    {
        if (curIndex >= digits.size())
        {
            if (curLetterComb != "")
                res.push_back(curLetterComb);
            return;
        }
        string possibleLetters = mp[digits[curIndex] - '0'];
        for (int i = 0; i < possibleLetters.size(); i++)
        {
            curLetterComb.push_back(possibleLetters[i]);
            dfs(res, mp, digits, curIndex + 1, curLetterComb);
            curLetterComb.pop_back();
        }
    }

    vector<string> letterCombinations(string digits)
    {
        vector<string> mp = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> res;
        string curLetterComb;
        dfs(res, mp, digits, 0, curLetterComb);
        return res;
    }
};
