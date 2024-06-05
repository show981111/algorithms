class Solution
{
    /**
     * Simple backtracking to iterate all possible combinations of words in WordDict.
     *
     * We can apply DP here. (from the back)
     * What is redundant?
     * < A > < B >
     * < A' > < B >
     * It will have the same split for < B >. However, DP is useless here.
     * Nothing is really redundant since we put different word to each position.
     *
     */
public:
    void solve(const string &s, const vector<string> &wordDict, string cur, int curIndex, vector<string> &ans)
    {
        if (curIndex == s.size())
        {
            ans.push_back(cur);
            return;
        }

        for (const string &w : wordDict)
        {
            if (s[curIndex] == w[0] && curIndex + w.size() <= s.size() && s.substr(curIndex, w.size()) == w)
            {
                string next = cur == "" ? w : cur + " " + w;
                // cout << next << endl;
                solve(s, wordDict, next, curIndex + w.size(), ans);
            }
        }
    }
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        vector<string> ans;
        solve(s, wordDict, "", 0, ans);
        return ans;
    }
};
