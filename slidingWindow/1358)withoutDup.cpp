/**
Challenge is how to count while keep TC O(N)
If we shrink the window, we loose the information about previous letters.
Then, for s = "abcabc", how can I count substrings that ends at "abca[b]c"?
Ex) if substring ends at [b], since we shrunk window, start would be "ab[c]abc"
How can I know that, there are more substrings like "[abcab]c" or "a[bcab]c"
*/
class Solution
{
public:
    int numberOfSubstrings(string s)
    {
        int freq[3] = {
            0,
        };
        int cnt = 0;

        int start = 0, end = 0;
        // a [b] c. [a]. b c -> cnt += start
        while (end < s.size())
        {
            freq[s[end++] - 'a']++;

            if (freq[0] > 0 && freq[1] > 0 && freq[2] > 0)
            {
                cnt += 1; // current string(start ~ end)
                while (1)
                {
                    freq[s[start++] - 'a']--; // push start
                    if (!(freq[0] > 0 && freq[1] > 0 && freq[2] > 0))
                    {
                        freq[s[--start] - 'a']++;
                        break;
                    } // if condition breaks, revert and break;
                }
                cnt += start; // we 0 ~ start + [current substring] make a desired substring. So, add start
                // ex) 0,1, 2, 3, ..., start + [cur_substr]
                // # substr = (start ~ [cur_substr]) + (start-1 ~ [cur_substr]) + (start-2 ~ [cur_substr])
                //          ... (2 ~ [cur_substr]) + (1 ~ [cur_substr]) + (0 ~ [cur_substr]). So, substr starting from 0 ~ start concat cur_substr makes desired substr!
            }
        }
        return cnt;
    }
};