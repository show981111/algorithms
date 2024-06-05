class Solution
{
public:
    string minRemoveToMakeValid(string s)
    {
        vector<int> lefts;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ')')
            {
                if (lefts.empty())
                    s[i] = '-';
                else
                    lefts.pop_back();
            }
            else if (s[i] == '(')
            {
                lefts.push_back(i);
            }
        }
        // Due to this process, we need to store the index. -> need a stack
        // can't just use int left and do ++ and --.
        while (lefts.size() > 0)
        {
            s[lefts.back()] = '-';
            lefts.pop_back();
        }
        s.erase(remove(s.begin(), s.end(), '-'), s.end());
        return s;
    }
};
/**
 * Well, if we just iterate back and do the same thing,
 * we can do without stack!
 */

class Solution
{
public:
    string minRemoveToMakeValid(string s)
    {
        int left = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ')')
            {
                if (left <= 0)
                    s[i] = '-';
                else
                    left--;
            }
            else if (s[i] == '(')
            {
                left++;
            }
        }
        int right = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (s[i] == '(')
            {
                if (right <= 0)
                    s[i] = '-';
                else
                    right--;
            }
            else if (s[i] == ')')
                right++;
        }
        s.erase(remove(s.begin(), s.end(), '-'), s.end());
        return s;
    }
};