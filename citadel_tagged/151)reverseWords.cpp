class Solution
{
public:
    string reverseWords(string s)
    {
        vector<string> words;

        string w;
        istringstream iss(s);
        while (iss >> w)
        {
            words.push_back(w);
        }
        string ans;
        for (auto iter = words.rbegin(); iter != words.rend(); ++iter)
        {
            ans += *iter;
            ans.push_back(' ');
        }
        ans.pop_back();
        return ans;
    }
};

/**
 * How to do O(1) space?
 * Why we needed a vector of strings?
 * To add words in reverse order to ans string.
 *
 * Can we make string stream give us the words in reverse order?
 * => Reverse the original string!!!
 *
 * Since the original string is reversed, each word is reversed too.
 * Thus, when u add the string to ans, reverse it!
 */

class Solution
{
public:
    string reverseWords(string s)
    {
        reverse(s.begin(), s.end());
        string ans;
        string w;
        istringstream iss(s);
        while (iss >> w)
        {
            reverse(w.begin(), w.end());
            ans += w;
            ans.push_back(' ');
        }
        ans.pop_back();
        return ans;
    }
};