/**
 * @brief DP for string comparison
 * Approach)
 * Comparing patterns... cannot use one array, we need 2D memo!
 * When we compare A[:i] vs B[:j]
 * T(i, j) = T(i-1, j-1) + extra condition...
 * We should first see A[:i-1] == B[:j-1], then compare current character A[i] vs B[j]
 *
 * In this problem we have three cases
 * 1) letter is alphabet 2) letter is '?' 3) letter is '*'
 *
 * For 1) and 2)
 * T(i,j) = T(i-1,j-1) && A[i] == B[j] # if letter is ?, then A[i] == B[j] is true all the time
 * If we use T(i,j-1) or T(i-1, j) we might double count it
 * ex) abb vs b
 *
 * For 3)
 * T(i,j) = T(i-1,j-1) || T(i,j-1) || T(i-1,j)
 * If we found the pattern before '*', after that pattern is always true!
 *
 * NOTE) in this case, * = ' ', so we should deal with this case when we init memo
 *
 *    ' ' a b c h a b c
 * ' ' T  F F F F F F F
 *  *  T  T T T T T T T
 *  b  F  F T F F F T F
 *  ?  F
 *  h  F
 *  *  F
 *  c  F
 *
 * We can use O(N) space if we only stores previous row!
 */

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        vector<vector<bool>> memo(p.size() + 1, vector<bool>(s.size() + 1, false));
        int rowSize = p.size() + 1;
        int colSize = s.size() + 1;

        memo[0][0] = true;
        for (int i = 1; i < rowSize; i++)
        {
            if (p[i - 1] == '*')
            {
                memo[i][0] = true;
            }
            else
                break;
        } // since * accepts empty sequence too

        for (int i = 1; i < rowSize; i++)
        {
            char colTarget = p[i - 1];
            for (int j = 1; j < colSize; j++)
            {
                if (colTarget == '?')
                {
                    memo[i][j] = memo[i - 1][j - 1];
                }
                else if (colTarget == '*')
                {
                    memo[i][j] = memo[i - 1][j - 1] || memo[i][j - 1] || memo[i - 1][j];
                }
                else
                {
                    memo[i][j] = memo[i - 1][j - 1] && (colTarget == s[j - 1]);
                }
            }
        }
        return memo[rowSize - 1][colSize - 1];
    }
};