/**
 * @brief Finding how many characters to delete
 * in order to make two strings equal
 *  == finding the Longest Common Sequence! and just subtract to get differences!
 *
 */

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        vector<int> memo(word2.size() + 1);
        int prev = 0, cur = 0;

        for (int i = 0; i < word1.size(); i++)
        {
            for (int j = 0; j < word2.size(); j++)
            {
                if (word1[i] == word2[j])
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
            memo[word2.size()] = cur;
            prev = 0; // reset prev
        }
        // cout << cur << endl;
        int ans = word1.length() - cur + word2.length() - cur;
        return ans;
    }
};