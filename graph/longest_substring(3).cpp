// O(s.length()^2)

class Solution
{
public:
    void resetArray(vector<int> &letters)
    {
        for (int i = 0; i < letters.size(); i++)
        {
            letters[i] = 0;
        }
    }
    int lengthOfLongestSubstring(string s)
    {
        vector<int> letters(128);
        int maxTotal = 0;

        for (int k = 0; k < s.length(); k++)
        {
            int curTotal = 0;
            for (int i = k; i < s.length(); i++)
            {
                if (letters[s[i] - ' '] == 0)
                {
                    curTotal++;
                    letters[s[i] - ' '] = 1;
                }
                else
                    break;
            }
            resetArray(letters);
            if (maxTotal < curTotal)
                maxTotal = curTotal;
        }
        return maxTotal;
    }
};