// Worst : O(s.length()^2)
// a lil better because it updates index to next to the redundant one
// Using array is much faster!
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        vector<int> letters(128, -1);
        /**
         * int letters[128];
         * fill(letters, letters + 128, -1);
         */
        int maxTotal = 0;
        int curTotal = 0;
        int started = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (letters[s[i] - ' '] == -1)
            {
                curTotal++;
                letters[s[i] - ' '] = i;
            }
            else
            {
                int stopped = i;
                i = letters[s[i] - ' '];
                // reset the part of array
                for (int k = started; k <= stopped; k++)
                    letters[s[k] - ' '] = -1;

                started = i + 1;
                curTotal = 0;
                if (s.length() - i < maxTotal)
                    break;
            }
            if (maxTotal < curTotal)
                maxTotal = curTotal;
        }
        return maxTotal;
    }
};

/**
 * @brief
 *
 */

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