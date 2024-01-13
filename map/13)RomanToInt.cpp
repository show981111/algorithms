class Solution
{
public:
    int romanToInt(string s)
    {
        unordered_map<char, int> mp = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

        int num = 0;
        int prev = 1001;
        for (const char &c : s)
        {
            if (prev >= mp[c])
            {
                num += mp[c];
            }
            else
            {
                num -= prev;
                num += mp[c] - prev;
            }
            prev = mp[c];
        }

        return num;
    }
};