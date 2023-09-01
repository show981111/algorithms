/**
 * @brief Use map to map pattern to the word!
 *
 */

class Solution
{
public:
    bool wordPattern(string pattern, string s)
    {
        unordered_map<char, string> mp;
        unordered_set<string> st;
        stringstream ss(s);
        string word;
        size_t wordCount = 0;
        while (ss >> word)
        {
            if (wordCount >= pattern.size())
            {
                return false;
            }
            if (mp.find(pattern[wordCount]) == mp.end())
            {
                mp[pattern[wordCount]] = word;
            }
            else
            {
                if (mp[pattern[wordCount]] != word)
                    return false;
            }
            st.insert(word);
            wordCount++;
        }
        if (st.size() != mp.size() || wordCount != pattern.size())
            return false;
        return true;
    }
};