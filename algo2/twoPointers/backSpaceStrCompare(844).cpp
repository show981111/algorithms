// O(n) time and O(1) space
  

class Solution
{
public:
    void applyBackSpace(string &st, int &index)
    {
        int backCount = 0;
        while (index >= 0 && (st[index] == '#' || backCount > 0))
        {
            if (st[index] == '#')
                backCount++;
            else
                backCount--;
            index--;
        }
    }

    bool backspaceCompare(string s, string t)
    {
        int i = s.length() - 1;
        int j = t.length() - 1;
        while (i >= 0 && j >= 0)
        {
            applyBackSpace(s, i);
            applyBackSpace(t, j); // get rightmost letter after applying all backspaces
            // cout << i << " " << j << endl;
            if (i < 0 && j < 0) // both are empty
                return true;
            else if (i < 0 || j < 0) // one of them are empty but the other is not
                return false;
            else if (s[i] == t[j])
            { // same, then go to next step
                i--;
                j--;
            }
            else // s[i] != t[j] // different, false
                return false;
        }
        /*
        I or J is < 0 since it breaks While
        */
        applyBackSpace(s, i); // apply backspace for remaining letters
        applyBackSpace(t, j);
        if (i < 0 && j < 0) // both are empty
            return true;
        else // one of them is not empty after applying backspaces => false
            return false;
    }
};