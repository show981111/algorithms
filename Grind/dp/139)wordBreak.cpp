/**
 * @brief Can we break this sentence with given words?
 * Simple Bottom-up DP
 * From the index where it is breakable, we investigate how far
 * we can break.
 *
 * Different Idea would be using a DFS however TLE due to substr which is O(N)
 * substring returns the copy of that section, so it is O(N)
 */

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        vector<bool> memo(s.size() + 1, false);
        memo[0] = true;

        for (int i = 0; i < memo.size(); i++)
        {
            if (memo[i])
            {
                for (int j = 0; j < wordDict.size(); j++)
                {
                    if (s.substr(i, wordDict[j].size()) == wordDict[j])
                    {
                        memo[i + wordDict[j].size()] = true;
                    }
                }
            }
        }

        return memo.back();
    }
    // DFS solution
    bool dfs(string &target, unordered_set<string> &st, int start)
    {
        if (target.length() == start)
            return true;
        bool res = false;
        for (int right = start; right < target.length(); right++)
        {
            if (st.find(target.substr(start, right - start + 1)) != st.end())
            {
                // cout << right << " ";
                res = dfs(target, st, right + 1);
                if (res)
                    return res;
            }
        }
        return res;
    }
};