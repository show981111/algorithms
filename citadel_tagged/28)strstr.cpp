/**
 * Simple sliding window string matching.
 *
 * Could use KMP...
 *
 * Also can use string.find()
 */

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        int nextPossible = -1;
        for (int i = 0; i < haystack.size();)
        {
            int j = 0;
            int start = i;
            while (i < haystack.size() && haystack[i] == needle[j])
            {
                i++;
                j++;
                if (i != start && haystack[i] == needle[0] && nextPossible == -1)
                {
                    nextPossible = i;
                }
                if (j == needle.size())
                    return start;
            }
            if (nextPossible != -1)
            {
                i = nextPossible;
                nextPossible = -1;
            }
            else
            {
                i++;
            }
        }
        return -1;
    }
};