/**
 * For position encoding/decoding
 * Usually, it is cyclic. => Use math to find the relationship!
 *
 */

class Solution
{
public:
    string convert(string s, int numRows)
    {
        /*
    0    P     I    N
    1    A   L S  I G
    2    Y A   H R
    3    P     I
        0123 21 0123 21 01
        PAYP AL ISHI RI NG
        0123 45 6789 1011 12 13
        */
        if (numRows == 1)
            return s;
        string converted = "";
        int curRow = 0;
        int step = numRows + (numRows - 2);
        int iter = 0;
        int cur = 0;

        while (converted.size() < s.size())
        {
            if (cur >= s.size())
            { // pushed all chars in that row
                curRow++;
                cur = curRow;
                if (cur >= s.size())
                    break; // cannot proceed more.
            }
            int interval = step - 2 * curRow;
            if (curRow != 0 && curRow != numRows - 1)
            {
                // add two if possible wihtin the cycle
                converted.push_back(s[cur]);
                if (cur + interval < s.size())
                    converted.push_back(s[cur + interval]);
                cur += step;
            }
            else
            {
                converted.push_back(s[cur]);
                cur += step;
            }
        }
        return converted;
    }
};