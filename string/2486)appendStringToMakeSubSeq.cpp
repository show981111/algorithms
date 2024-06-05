class Solution
{
public:
    /*
    Append minimum number of chars in t to make appended s a subsequence of s!
    -> Get the Logest PREFIX of s and t. Then, append rest to s.

    Note: it shouldn't be a Longest Common Subsequence.
    For example if s = "coaching" and t = "cnahing"
    Length of LCS is "ching" = 5. However, we need all letters in T to appear in order.
    Since s doesn't have "n" and "a" we cannot make "cnahing" by just appending the rest.
    */
    int appendCharacters(string s, string t)
    {
        int longest_pre = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (t[longest_pre] == s[i])
                longest_pre++;
        }
        return t.size() - longest_pre;
    }
};
