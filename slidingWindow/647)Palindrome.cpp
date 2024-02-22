class Solution
{
public:
    /*
    Substring == subarray -> DP or sliding window?
    Total O(N^2) number of substrings.
    checking a palindrome for each of them will O(N^3)
    Can we use sliding window to make it O(N^2)?

    Be careful of even length palindrome. When we set the center, we can
    extend in both way to get odd length palidrome.
    For even length, we should extend from the two neighboring center!
    */

    int countSubstrings(string s)
    {
        int cnt = 0;
        for (int center = 0; center < s.size(); ++center)
        {
            int l = center, r = center;

            // will count odd length ones
            while (l >= 0 && r < s.size() && s[l] == s[r])
            {
                cnt++;
                l--;
                r++;
            }
            // count the even ones
            if (center + 1 <= s.size())
            {
                l = center;
                r = center + 1;
                while (l >= 0 && r < s.size() && s[l] == s[r])
                {
                    cnt++;
                    l--;
                    r++;
                }
            }
        }

        return cnt;
    }
};