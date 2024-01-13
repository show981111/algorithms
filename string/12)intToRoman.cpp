/**
 * Traverse integer like array.
 */
class Solution
{
public:
    string intToRoman(int num)
    {
        unordered_map<int, char> mp = {
            {1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};
        string ans = "";

        int topNum = 1000;
        while (num > 0)
        {
            int d = num / topNum;
            num -= d * topNum;
            // cout << d * topNum << " - " << topNum << " " << num << ". ";
            // need to build d * topNum;
            if (d == 0)
            {
                // no-op
            }
            else if (d == 4)
            { // 400 -> 100 500
                ans.push_back(mp[1 * topNum]);
                ans.push_back(mp[5 * topNum]);
            }
            else if (d == 9)
            {
                ans.push_back(mp[1 * topNum]);
                ans.push_back(mp[10 * topNum]);
            }
            else
            {
                if (d >= 5)
                {
                    ans.push_back(mp[5 * topNum]);
                    d -= 5;
                }
                for (int i = 0; i < d; i++)
                {
                    ans.push_back(mp[topNum]);
                }
            }
            topNum = topNum / 10;
        }
        return ans;
    }
};