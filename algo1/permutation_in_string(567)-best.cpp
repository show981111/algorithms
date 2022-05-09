/*
Enhance performace by replacing a for-loop which checks all items are zero
into counting the number of uniqueLetter
*/

class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        int freq[26] = {
            0,
        };
        int uniqueLetter = 0;
        for (int i = 0; i < s1.length(); i++)
        {
            if (++freq[s1[i] - 'a'] == 1)
                uniqueLetter++;
        }

        int startWindowIndex = 0;
        int step = startWindowIndex;
        int uniqueMatched = 0;
        while (step < s2.length())
        {
            if (--freq[s2[step] - 'a'] == 0) // freq becomes 1 to 0
                uniqueMatched++;             // that means, s2[step] contains an uniqueLetter with right amount
            if (step + 1 < s1.length())
                step++;
            else
            {
                if (uniqueMatched == uniqueLetter)
                {
                    return true;
                }
                if (++freq[s2[startWindowIndex] - 'a'] == 1) // freq becomes 0 to 1
                    uniqueMatched--;                         // that means, s2[startWindowIndex] was a unique letter
                startWindowIndex++;
                step++;
            }
        }
        return false;
    }
};