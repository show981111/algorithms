/**
 * @brief Similar to LCS!
 *
 * Same 2D memo : The min number of operations to convert col -> row
 * 0 index is working as a buffer or just an empty string.
 *
 * 2 cases
 * 1) word1[i] == word2[j]
 *      T(row, col) = T(row-1, col-1)
 *      if letters are the same, we do not need to do more operations.
 *      so it's the same as T(row-1, col-1)
 * 2) word1[i] != word2[j]
 *      We have 3 cases in here
 *      a) T(row-1,col)
 *      b) T(row, col-1)
 *          For a) and b) we can add 1 operation to make word1[:i] == word2[:j]
 *          from previous step
 *      c) T(row-1, col-1)
 *          since we have a REPLACEMENT, we can just replace word1[i] -> word[j]
 *          So unlink LCS, we should consider this step.
 *          ex) "in" -> "ex"
 *              -  e  x
 *            - 0  1  2
 *            i 1 [1] 2   We can make "i" -> "e" by replacing it
 *            n 2  2 [2]  We can make "in" -> "ex" by replacing "n" -> "x" with converting "i" -> "e"
 *          Thus, T(row, col) = min(T(row-1,col), T(row, col-1), T(row-1, col-1)) + 1
 *
 */

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        vector<vector<int>> memo(word1.size() + 1, vector<int>(word2.size() + 1));
        iota(memo[0].begin(), memo[0].end(), 0);
        for (int i = 0; i < word1.size() + 1; i++)
            memo[i][0] = i;
        // set buffer
        for (int i = 0; i < word1.size(); i++)
        {
            for (int j = 0; j < word2.size(); j++)
            {
                if (word1[i] == word2[j])
                {
                    memo[i + 1][j + 1] = memo[i][j];
                }
                else
                {
                    memo[i + 1][j + 1] = min(memo[i][j], min(memo[i + 1][j], memo[i][j + 1])) + 1;
                }
            }
        }

        return memo[word1.size()][word2.size()];
    }
};