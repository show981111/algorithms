/**
 * @brief
 * Since we have two strings, and compare them, we need 2D memo
 *
 * There are two cases.
 * 1) when each letter is the same
 *      if that letter is the same, we should determine that letter can be used to
 *      increase the subsequence. So, we should see memo[i-1][j-1] which is the result of
 *      subsequence without that specific letter.
 *      Thus, memo[i-1][j-1]
 * => if we just add 1 to the max(memo[i - 1][j], memo[i][j - 1]), we can double count the letter
 * that was already used to increase the length of subsequence
 *
 * EX)
 *   a b c e d
 * a 1 1 1 1 1
 * c 1 1 2 2 2
 * c 1 1 3 => this is wrong because c is already counted when we compare abced vs ac
 *
 * 2) different
 *      max(memo[i - 1][j], memo[i][j - 1])
 *      since that letters are different, we should choose max from previous one.
 *      since memo[i][j] contains both memo[i - 1][j], memo[i][j - 1], we should use max!
 *
 * TIME : O(MN), SPACE : O(MN)
 *
 * PS) When we are making the memo array
 * we could make it as memo[a.size()+1][b.size()+1] so we can use 0 index as a buffer.
 * Then we do not have to repeat for loop for setting 0index.
 */

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        vector<vector<int>> memo(text1.size(), vector<int>(text2.size()));
        bool foundMatch = false;
        for (int i = 0; i < text2.size(); i++)
        {
            if (text2[i] == text1[0] || foundMatch)
            {
                memo[0][i] = 1;
                foundMatch = true;
            }
        }
        // set the first row
        foundMatch = false;
        for (int j = 0; j < text1.size(); j++)
        {
            if (text1[j] == text2[0] || foundMatch)
            {
                memo[j][0] = 1;
                foundMatch = true;
            }
        }
        // set the first column
        for (int i = 1; i < text1.size(); i++)
        {
            for (int j = 1; j < text2.size(); j++)
            {
                if (text1[i] == text2[j])
                {
                    memo[i][j] = memo[i - 1][j - 1] + 1;
                }
                else
                {
                    memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
                }
            }
        }
        //         for(int i = 0; i < text1.size(); i++){
        //             for(int j = 0; j < text2.size(); j++){
        //                 cout << memo[i][j] << " ";
        //             }
        //             cout << endl;
        //         }

        return memo[text1.size() - 1][text2.size() - 1];
    }
};

/**
 * @brief If we are using a buffer then,
 *
 */
class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        vector<vector<int>> memo(text1.size() + 1, vector<int>(text2.size() + 1));

        for (int i = 0; i < text1.size(); i++)
        {
            for (int j = 0; j < text2.size(); j++)
            {
                if (text1[i] == text2[j])
                {
                    memo[i + 1][j + 1] = memo[i][j] + 1;
                }
                else
                {
                    memo[i + 1][j + 1] = max(memo[i + 1][j], memo[i][j + 1]);
                }
            }
        }
        return memo[text1.size()][text2.size()];
    }
};
/**
 * @brief Since we are using prev column or prev row,
 * We can reduce memo to 1D memo, only memorizing the previous Row!
 *
 * Time : O(MN), SPACE : O(N)
 */

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        vector<int> memo(text2.size() + 1);
        int prev = 0, cur = 0;

        for (int i = 0; i < text1.size(); i++)
        {
            for (int j = 0; j < text2.size(); j++)
            {
                if (text1[i] == text2[j])
                {
                    cur = memo[j] + 1; // cur = memo[i+1][j+1]
                }
                else
                {
                    cur = max(prev, memo[j + 1]);
                }
                memo[j] = prev;
                prev = cur;
            }
            memo[text2.size()] = cur;
            prev = 0; // reset prev
        }

        return cur;
    }
};
