class Solution
{
public:
    /*
    Odd number -> Last digit of binary number should be one
    */
    string maximumOddBinaryNumber(string s)
    {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '1')
                cnt++;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (i < cnt - 1)
                s[i] = '1';
            else
                s[i] = '0';
        }
        s.back() = '1';
        return s;
    }
};