class Solution
{
public:
    /*
    1. Length of suffix and prefix can differ
    2. All characters in suffix and prefix should be the same
    Return min length after removing prefix & suffix any number of times
    */
    int minimumLength(string s)
    {
        int l = 0, r = s.size() - 1;

        while (l < r)
        {
            if (s[l] == s[r])
            {
                // can remove
                while (l + 1 < r && s[l] == s[l + 1])
                {
                    l++;
                }
                while (l < r - 1 && s[r - 1] == s[r])
                {
                    r--;
                }
                // remove them
                l++;
                r--;
            }
            else
            {
                break;
            }
        }

        return r - l + 1;
    }
};