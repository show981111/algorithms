class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        int arr[30] = {
            0,
        };
        for (char &c : s)
        {
            arr[c - 'a']++;
        }
        for (char &c : t)
        {
            arr[c - 'a']--;
        }
        for (int i = 0; i < 30; i++)
            if (arr[i] != 0)
                return false;
        return true;
    }
};
/**
 * @brief Other way. only two iteration!
 */
class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
            return false;
        int arr[30] = {
            0,
        };
        for (int i = 0; i < s.length(); i++)
        {
            arr[s[i] - 'a']++;
            arr[t[i] - 'a']--;
        }
        for (int i = 0; i < 30; i++)
            if (arr[i] != 0)
                return false;
        return true;
    }
};