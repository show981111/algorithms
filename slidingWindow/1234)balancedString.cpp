/**
 * @brief Key of this problem is finding out the condition of sliding window.
 * Usually sliding window has a condition that allows me to how far I can go.
 * This one, that condition is offset[0] <= 0 && offset[1] <= 0 && offset[2] <= 0 && offset[3] <= 0
 * Why? So we can change anything in the subtring to anything we want. So, as long as we contain
 * all letters that are execssive, we can switch them to letters that are short.
 * ex) Q: 4, E: 4, R: 2, W:2  (target = 3) So if we contain, one Q, and one E, then we can
 * change them to R and W to make a balanced string.
 * Thus, key is Counting if we have all exessive letters!
 *
 * Then, problem gets simpler
 *
 */

class Solution
{
public:
    int charToIndex(char c)
    {
        if (c == 'Q')
            return 0;
        else if (c == 'W')
            return 1;
        else if (c == 'E')
            return 2;
        else if (c == 'R')
            return 3;
        return -1;
    }
    int balancedString(string s)
    {
        int target = s.size() / 4;
        int offset[4] = {-target, -target, -target, -target};
        for (char &c : s)
        {
            offset[charToIndex(c)]++;
        }
        if (offset[0] == 0 && offset[1] == 0 && offset[2] == 0 && offset[3] == 0)
            return 0;

        int minLength = s.size();
        int start = 0, end = 0;
        // minimum length of contiguous non zero offset that is at least needToCHange,
        while (end < s.size())
        {
            // Need offset Amount of each letter!
            offset[charToIndex(s[end++])]--;

            while (start < end && offset[0] <= 0 && offset[1] <= 0 && offset[2] <= 0 && offset[3] <= 0)
            {
                offset[charToIndex(s[start++])]++;
                minLength = min(minLength, end - start + 1);
            }
        }

        return minLength;
    }
};