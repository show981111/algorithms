/**
 * @brief DP with Subsequence! usually includes 2D memo with one string and the other one
 *
 * Problem:
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.
 *
 * How can we count the number of distinct subsequences?
 * Let's look for relationship with n and n-1
 * EX) S = rabbbit , T = rabbit.
 * Suppose the number of distinct subseq in S is X when T = rabb,
 * Then, if T = rabbi, We should first look how many subsequences of "rabb" is in S, from [0:i]
 * (i is the index where S[i] == T[i] == 'i')
 * Then, if we find "i" in S, we can just simply use that number.
 * Key here is we should add the newly found number to previous number.
 * it means,
 * (A) when we include current letter : memo[i-1][j-1] (t[i] == s[j])
 * (B) when we do not include current letter : memo[i][j-1]
 *
 * Thus, T(row, col) = T(row, col-1) if(t[row] != s[col])
 *       T(row, col) = T(row, col-1) + T(row-1,col-1) if(t[row] == s[col])
 *
 * Initialization.
 * if we put " " empty character in front of both string, then there is a 1 subsequence
 * for S and ' '. So, memo[0][:S] = 1
 *
 * EX)
 *   - r a b b b i t [S]
 * - 1 1 1 1 1 1 1 1 (initialized)
 * r 0 1 1 1 1 1 1 1
 * a 0 0 1 1 1 1 1 1
 * b 0 0 0 1 2 3 3 3
 * b 0 0 0 0 1 3 3 3
 * i 0 0 0 0 0 0 3 3
 * t 0 0 0 0 0 0 0 3
 * [T]
 */

class Solution
{
public:
    int numDistinct(string s, string t)
    {
        if (t.length() > s.length())
            return 0;
        int T = t.size(), S = s.size();
        vector<vector<unsigned long>> memo(T + 1, vector<unsigned long>(S + 1, 0));
        for (int i = 0; i < S + 1; i++)
            memo[0][i] = 1; // empty string and string s...

        for (int i = 1; i < T + 1; i++)
        {
            for (int j = 1; j < S + 1; j++)
            {
                if (t[i - 1] == s[j - 1])
                    memo[i][j] = memo[i][j - 1] + memo[i - 1][j - 1];
                else
                    memo[i][j] = memo[i][j - 1];
            }
        }

        return memo[T][S];
    }
};