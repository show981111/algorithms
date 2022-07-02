class Solution
{
public:
    int longestPalindrome(string s)
    {
        int larr[60] = {
            // When we don't know 'A' ~ 'z' size, we can use 'z' - 'A' + 1
            0,
        };
        int leng = 0;
        for (auto &c : s)
        {
            larr[c - 'A']++;
            if (larr[c - 'A'] == 2)
            {
                leng += 2;
                larr[c - 'A'] = 0;
            }
        }

        if (s.length() - leng >= 1)
            leng += 1;
        return leng;
    }
};