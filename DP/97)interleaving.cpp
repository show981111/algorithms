/**
 * @file 97)interleaving.cpp
 * Backtracking + Memoization
 * We can solve this as a pure DP too.
 *
 * dp[i][j] => we can construct s3[i+j] with s1[:i], s2[:j]
 */

class Solution
{
public:
    vector<vector<int>> memo;
    bool backTrack(string &s1, string &s2, string &s3, int s1Index, int s2Index, int s3Index)
    {
        if (s3Index >= s3.size())
        {
            return true;
        }
        if (memo[s1Index][s2Index] != 0)
        {
            return memo[s1Index][s2Index] == 1 ? true : false;
        }
        bool res = false;
        if (s1Index < s1.size() && s3[s3Index] == s1[s1Index])
        {
            res = backTrack(s1, s2, s3, s1Index + 1, s2Index, s3Index + 1);
        }

        if (!res && s2Index < s2.size() && s3[s3Index] == s2[s2Index])
        {
            res = backTrack(s1, s2, s3, s1Index, s2Index + 1, s3Index + 1);
        }
        memo[s1Index][s2Index] = res ? 1 : -1;
        return res;
    }
    bool isInterleave(string s1, string s2, string s3)
    {
        if (s1.size() + s2.size() != s3.size())
            return false;
        memo.resize(s1.size() + 1, vector<int>(s2.size() + 1, 0));
        return backTrack(s1, s2, s3, 0, 0, 0);
    }
};