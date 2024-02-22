/**
 * @brief AND [left, right]
 * Key is Removing the rightmost '1' until left <= right
 *
 * https://leetcode.com/problems/bitwise-and-of-numbers-range/discuss/56721/2-line-Solution(the-fastest)-with-detailed-explanation
 */

class Solution
{
public:
    /*
    How many rightmost bits we can erase?
    It is known that k & (k-1) will remove the rightmost bit of k
    */
    int rangeBitwiseAnd(int left, int right)
    {
        // O(32) since there are total 32 bits we can remove
        while (left < right)
        {
            // starting from right, proceed until left < right
            // if right - 1 is in [left, right]
            // we can for sure remove the rightmost bit.
            // So, no need to explore [right & (right - 1) ~ right -1]
            // go straight to right & (right - 1)
            // if left == right, should just return right since right -1 is not in the range
            right = right & (right - 1);
        }
        // Equivantely
        // while (left <= right - 1)
        // {
        //     right = right & (right - 1);
        // }
        // return right;
        return right;
    }
};
/**
 * @brief Another solution
 * Key is finding the matching part
 * XXXqwer ~ XXXasdf => XXX0000 is the result of AND
 * if left != right, then there must be
 * an odd and even number. so AND result is =0
 *
 * Suppose the matching part is XXX
 * ex) right = XXX10010
 * XXX00000 <= left < XXX10000 if left = XXX10000 then the matching part is XXX1
 * left must include XXX10001, and XXX0abcd, so the result is XXX00000
 */
class Solution
{
public:
    int rangeBitwiseAnd(int left, int right)
    {
        if (right == 0)
        {
            return 0;
        }
        int moveFactor = 1;
        while (right != left)
        {
            right >>= 1;
            left >>= 1;
            moveFactor <<= 1;
        }
        return right * moveFactor;
    }
};