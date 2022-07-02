/**
 * @brief Binary Adder
 * AB + CD =>
 * SUM = A^B^Carry
 * (1 + 1  = 0, 1 + 0 = 1, but considering carry, 1+1+1 = 1, 1+0+1 = 0... the number of '1' is odd,
 * then SUM =1 , even : 0)
 * CARRY = AB+BC+AC, if there are more than two '1's,  then CARRY = 1.
 *
 * ^ is XOR in cpp!!
 *
 * WORTH NOTING
 * http://codeforces.com/blog/entry/66660
 */

class Solution
{
public:
    string addBinary(string a, string b)
    {
        int aSize = a.size() - 1;
        int bSize = b.size() - 1;
        bool carry = false;
        string &ans = aSize > bSize ? a : b;
        int index = aSize > bSize ? aSize : bSize;

        while (aSize >= 0 || bSize >= 0)
        {
            int aCur = aSize >= 0 ? a[aSize] - '0' : 0;
            int bCur = bSize >= 0 ? b[bSize] - '0' : 0;

            int sum = (aCur ^ bCur) ^ carry;                         // SUM
            carry = (aCur & bCur) | (bCur & carry) | (aCur & carry); // CARRY
            ans[index--] = sum + '0';
            aSize--;
            bSize--;
        }
        if (carry)
            ans = '1' + ans;
        return ans;
    }
};