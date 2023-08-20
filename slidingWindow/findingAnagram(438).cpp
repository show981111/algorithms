/*
Sliding window:
    Time: O(n), Space: O(n) for result vector
*/

class Solution
{
public:
    bool isAnagram(int *arr)
    {
        for (int i = 0; i < 25; i++)
            if (arr[i] != 0)
                return false;
        return true;
    }
    vector<int> findAnagrams(string s, string p)
    {
        if (s.length() < p.length())
            return vector<int>();
        vector<int> res;
        int freq[26] = {
            0,
        };
        for (auto iter = p.begin(); iter != p.end(); ++iter)
        {
            freq[*iter - 'a']++;
        }

        int windowSize = p.length();
        // check for first window
        for (int i = 0; i < windowSize; i++)
        {
            freq[s[i] - 'a']--;
        }
        if (isAnagram(freq))
        {
            res.push_back(0);
        }
        // initial case check done

        // moving window forward and check
        for (int i = 1; i <= s.length() - windowSize; i++)
        {
            freq[s[i - 1] - 'a']++;
            freq[s[i + windowSize - 1] - 'a']--;
            if (isAnagram(freq))
            {
                res.push_back(i);
            }
        }
        return res;
    }
};
