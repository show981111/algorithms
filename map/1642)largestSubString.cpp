class Solution
{
    /**
     * Key is how to retrive the past location of character?
     * Just going from the leftmost and rightmost is not enough,
     * since we don't know which one to move. Move right index to -1? or left index to +1?
     * Key is, as we iterate the array, we record the min position. Then, later, if we find the
     * same character, then we use tha to compute the longest substring!
     */
public:
    int maxLengthBetweenEqualCharacters(string s)
    {
        unordered_map<char, int> mp;
        int m = -1;
        for (int i = 0; i < s.size(); i++)
        {
            if (mp.count(s[i]) > 0)
            {
                m = max(m, i - mp[s[i]] - 1);
            }
            else
            {
                mp[s[i]] = i;
            }
        }
        return m;
    }
};
