/**
 * @brief Typical sliding window => most of them can be O(N)
 *
 * Three part of solving sliding window
 *
 * (A) moving forward (at each step, increase right)
 * (B) shrinking (use a while loop to shrink left)
 *  Then,
 * (C) Update Answer
 */

class Solution
{
public:
    string minWindow(string s, string t)
    {
        unordered_map<char, int> mp;
        for (char &c : t)
        {
            mp[c]--;
        }

        int left = 0, right = 0;
        int ansSize = s.size() + 1;
        int ansLeft;
        while (left < s.size() && right < s.size())
        {
            // update MAP
            if (mp.find(s[right]) != mp.end() && right < s.size())
            {
                mp[s[right]]++;
            }
            if (right < s.size())
            {
                right++;
            }

            // Checking it contains all letter
            bool containsAllLetter = true;
            for (auto &iter : mp)
            {
                if (iter.second < 0)
                {
                    containsAllLetter = false;
                    break;
                }
            }

            // shrink as far as we can
            if (containsAllLetter)
            {
                while (left < s.size() && (mp.find(s[left]) == mp.end() || mp[s[left]] > 0))
                {
                    if (mp.find(s[left]) != mp.end())
                        mp[s[left]]--;
                    left++;
                }

                // update answer
                if (right - left < ansSize)
                {
                    ansSize = right - left;
                    ansLeft = left;
                }
            }
        }

        return ansSize != s.size() + 1 ? s.substr(ansLeft, ansSize) : "";
    }
};