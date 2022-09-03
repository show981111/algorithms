/**
 * @brief Sliding Window
 * Why sliding window?
 * we are counting something consecutive in Array.
 * Subarray or Substring! => sliding window!
 *
 * just use [) sliding window,
 * and check when right == s.size()!
 *
 */
class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        if (s.size() < p.size())
            return vector<int>();
        int mp[26] = {
            0,
        };
        for (auto &c : p)
            mp[c - 'a']++;
        vector<int> ans;
        int left = 0, right = 0;
        while (left < s.size())
        {
            if (right < p.size())
            {
                while (right < p.size())
                {
                    mp[s[right++] - 'a']--;
                }
            }
            bool isAnagram = true;
            for (int i = 0; i < 26; i++)
            {
                if (mp[i] != 0)
                {
                    isAnagram = false;
                    break;
                }
            }
            if (isAnagram)
                ans.push_back(left);
            mp[s[left++] - 'a']++;
            if (right == s.size())
                break;
            mp[s[right++] - 'a']--;
        }
        return ans;
    }
};
