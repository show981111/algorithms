/**
 * @brief Monotonic Stack -> Can be used for Ordering problems
 *
 */

class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        int freq[26] = {
            0,
        };
        bool inRes[26] = {
            false,
        };

        for (char &c : s)
        {
            freq[c - 'a']++;
        }
        string ans;

        // How to get smallest lexicographical order?
        // we know which letters will be there but..
        // thinking about sorting but not possible.. how do I know
        // there is a bigger letter or not? how to store positions if there are
        // multiple characters?

        // Lots of sequence questions can be solved while iterating
        // from the beginning!

        for (int i = 0; i < s.size(); i++)
        {
            freq[s[i] - 'a']--;

            // not in result set, lets put this in.
            if (inRes[s[i] - 'a'] == false)
            {
                // find where s[i] should go!
                while (ans.size() > 0 && ans.back() > s[i] // if s[i] is lexicographically smaller, s[i] should go first
                       && freq[ans.back() - 'a']           // only if ans.back() can come after s[i]
                                                           // which means, there is ans.back() after s[i]
                                                           // if not, cannot move s[i] in front of ans.back() because
                                                           // unique elem should be there with original ordering
                )
                {
                    inRes[ans.back() - 'a'] = false;
                    ans.pop_back();
                }
                inRes[s[i] - 'a'] = true;
                ans.push_back(s[i]); // now we should add this because it is not in the res. and Unique elem should be there.
            }
        }

        return ans;
    }
};