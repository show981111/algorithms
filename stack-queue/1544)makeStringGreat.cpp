class Solution
{
public:
    /*
    How to defer erasing elements?
    Or, can we delay shifting?
    If inplace modification is hard, think about creating a new container
    and put the answer there.

    Now we have new container, can we put everything in O(N)?
    Everytime we mark the elem as erased, we need to go back until we find
    non-erased char. Then if that char is erased, need to do the same thing.
    => STACK? we push new elem, pop it, and go back to the old elem!
    Keep left chars in the stack, and move right pointer in the string.
    */
    bool isBad(char a, char b)
    {
        // if((toupper(a) == b && a == tolower(b)) ||
        //     (tolower(a) == b && a == toupper(b))){
        //     return true;
        // }
        // return false;
        return abs(a - b) == 'a' - 'A';
    }
    string makeGood(string s)
    {
        if (s.size() == 1)
            return s;
        int r = 0;
        string ans;
        ans.push_back(s[r++]);
        while (r < s.size())
        {
            if (isBad(ans.back(), s[r]))
            {
                ans.pop_back();
                if (ans.empty() && r + 1 < s.size())
                {
                    ans.push_back(s[r + 1]);
                    r = r + 2;
                }
                else
                {
                    r++;
                }
            }
            else
            {
                ans.push_back(s[r++]);
            }
        }
        return ans;
    }
};