class Solution
{
public:
    vector<string> findAndReplacePattern(vector<string> &words, string pattern)
    {
        unordered_map<char, char> fromTo; // from -> dest
        unordered_map<char, char> toFrom; // dest -> from
        vector<string> ans;
        int N = pattern.size();
        for (auto &w : words)
        {
            int i = 0;
            for (i = 0; i < N; i++)
            {
                if (fromTo.find(w[i]) == fromTo.end() && toFrom.find(pattern[i]) == toFrom.end())
                {
                    fromTo[w[i]] = pattern[i];
                    toFrom[pattern[i]] = w[i];
                }
                else if (fromTo.find(w[i]) != fromTo.end())
                {
                    if (fromTo[w[i]] != pattern[i])
                        break;
                }
                else
                { // toFrom(pattern[i]) != toFrom.end()
                    if (toFrom[pattern[i]] != w[i])
                        break;
                }
            }
            if (i == w.size())
                ans.push_back(move(w));
            fromTo.clear();
            toFrom.clear();
        }
        return ans;
    }
};