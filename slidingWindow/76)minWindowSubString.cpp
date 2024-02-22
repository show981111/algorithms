/**
 * Sliding Window With Map (common)
 *
 * Move end once at a time, end++,
 * then evaluate and shrink so that we can consider every case that ends at that END
 */

class Solution
{
public:
    // bool targetReached(vector<int> &targetCnt)
    // {
    //     for (int i = 0; i < 60; i++)
    //     {
    //         if (targetCnt[i] > 0)
    //             return false;
    //     }
    //     return true;
    // }
    string minWindow(string s, string t)
    {
        vector<int> targetCnt(60, 0);
        for (char c : t)
            targetCnt[c - 'A']++;
        int ansStart = -1, ansEnd = 2 * s.size();
        int cnt = t.size(); // cnt for target letters

        int start = 0, end = 0;

        while (end < s.size())
        {
            if (targetCnt[s[end++] - 'A']-- > 0) // end is at Next End
                cnt--;                           // effectively removed one target letter

            while (start < end && cnt == 0)
            {
                if (end - start < ansEnd - ansStart)
                {
                    ansEnd = end;
                    ansStart = start;
                }
                // remove s[start] from the window (shrink)
                if (targetCnt[s[start++] - 'A']++ >= 0) // if it becomes positive, target letter got removed.
                    cnt++;
                // For non-target letters, max targetCnt will be 0 since we subtract and add which will offset
                // since initial targetCnt was 0
            }
        }

        if (ansStart == -1)
            return "";
        else
            return s.substr(ansStart, ansEnd - ansStart); // end already added one abive
    }
};