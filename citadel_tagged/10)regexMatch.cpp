/**
 * String match 99% DP
 *
 * T(i,j) = p[0:i] matches s[0:j]
 *
 * If p[i] == '*'
 *    1) Use prev char: p[i-1] == s[j] && dp[i][col-1] (pattern is so far matching + preceding char is equal to cur char of s)
 *    2) Make * just empty (one match of preceding char): dp[i - 1][j]
 *    3) Zero matching of previous char : dp[i-2][j] -> Treat preceding char and * as empty
 * If p[i] == '.' or letter
 *    1) T(i-1,j-1) && p[i] == s[i] -> p[i-1] and s[i-1] are matching and current char are the same
 *
 * BASE CASE
 *    - Add empty char at 0 index as a buffer. Empty char is matching with Empty char so dp[0][0] = True.
 *    - If p is *, then it can make itself empty or itself and preceding element empty ex) "c*" == '', so dp[i][0] = dp[i - 2][0];
 */

class Solution
{
public:
    bool charCmp(char a, char b)
    {
        return a == b || a == '.';
    }

    bool isMatch(string s, string p)
    {
        vector<vector<bool>> dp(p.size() + 1, vector<bool>(s.size() + 1, false));
        dp[0][0] = true;
        for (int i = 0; i < p.size(); i++)
        {
            if (p[i] == '*')
            {
                if (i - 1 < 0)
                    dp[i + 1][0] = true;
                else
                {
                    dp[i + 1][0] = dp[i - 1][0];
                }
            }
        }

        for (int row = 1; row <= p.size(); ++row)
        {
            for (int col = 1; col <= s.size(); ++col)
            {
                if (p[row - 1] == '*')
                {
                    dp[row][col] = (charCmp(p[(row - 1) - 1], s[col - 1]) && dp[row][col - 1]) || dp[row - 1][col];
                    if (row - 2 >= 0)
                        dp[row][col] = dp[row][col] || dp[row - 2][col];
                }
                else
                {
                    dp[row][col] = dp[row - 1][col - 1] && charCmp(p[row - 1], s[col - 1]);
                }
            }
        }
        return dp[p.size()][s.size()];
    }
};