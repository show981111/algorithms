class Solution
{
    /**
     * Getting an intersection of letters among different strings!
     * Use minimum to get an intersection!!!
     */
public:
    vector<string> commonChars(vector<string> &words)
    {
        const int MAXFREQ = 101;
        vector<int> commonLetters(26, MAXFREQ);
        int N = words.size();
        for (int i = 0; i < words.size(); i++)
        {
            vector<int> letters(26, 0);
            for (char &c : words[i])
            {
                letters[c - 'a']++;
            }
            for (int k = 0; k < 26; k++)
            {
                commonLetters[k] = min(commonLetters[k], letters[k]);
            }
        }
        vector<string> v;
        for (int i = 0; i < 26; i++)
        {
            string s{static_cast<char>(i + 'a')};
            for (int j = 0; j < commonLetters[i]; j++)
            {
                v.push_back(s);
            }
        }

        return v;
    }
};
