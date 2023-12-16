/**
 * Classic palindrome DP
 *
 * Brute force will be O(N^3)
 * Total N^2 substring, for each substring, check if they are palindrome O(N) => O(N^3)
 */

class Solution
{
public:
    int countSubstrings(string s)
    {
        /*
           T(i,j): s[i:j] is palindrome
           T(i,j) = T(i+1,j-1) && s[i] == s[j]
           Base case =
             ' a b b d
           '
           a   T F F F
           b.    T T T
           b.      T
           d         T
        */
        int num = 0;
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), true));

        for (int offset = 0; offset < s.size(); ++offset)
        {
            for (int row = 0; row < s.size() - offset; ++row) // Diagonal traverse. Cannot go all the way to the end of the row if offset > 0 so - offset!
            {
                int col = row + offset;
                if (row == col)
                {
                    dp[row][col] = true;
                }
                else
                {
                    dp[row][col] = s[row] == s[col] && dp[row + 1][col - 1];
                }
                if (dp[row][col])
                    num++;
            }
        }
        return num;
    }
};

/**
 * Different traverse pattern.
 * For each col, bottom up from the row = col_index
 *
 */
class Solution
{
public:
    int countSubstrings(string s)
    {
        int num = 0;
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), true));

        for (int col = 0; col < s.size(); ++col)
        {
            for (int row = col; row >= 0; --row)
            {
                if (col != row)
                {
                    dp[row][col] = s[row] == s[col] && dp[row + 1][col - 1];
                }
                if (dp[row][col])
                    ++num;
            }
        }
        return num;
    }
};