/**
 * @brief Dividing two integers.. if it is slow,,, use shifting!
 * 58/3 ??
 * 58 = 2^4*3 + 2^1 * 3 + 2^0 * 3 + (1)
 *    = (2^4 + 2^1 + 2^0) * 3 + 1
 * => [58 - 2^4*3] = 2^1 * 3 + 2^0 * 3 + 1  ==> recursive step! At each step, just find maximum
 *                                               amount we can subtract using 2^k and divisor!
 */

class Solution
{
public:
    long divHelper(long dividend, long quo, long divisor, bool isNeg)
    {
        if (dividend < divisor)
            return quo;
        if (dividend == divisor)
        {
            return 1 + quo;
        }
        // 3 = 2 * 1 + 1
        long twoMul = 1;
        long prevTwoMul = 1;
        long prevMulResult = divisor;
        long mulResult = divisor * twoMul;
        while (mulResult < dividend)
        {
            prevMulResult = mulResult;
            prevTwoMul = twoMul;
            twoMul = twoMul << 1;
            mulResult = divisor * twoMul;
        }

        long r = divHelper(dividend - prevMulResult, prevTwoMul, divisor, isNeg);
        // cout << "R: " << r + temp << endl;
        long f = quo + r;
        return f;
    }

    int divide(int dividend, int divisor)
    {
        // 18 = 2^2*4 + 2 => 2
        // return wtf(dividened, divisor);
        bool isNeg = false;
        // cout << "hi\n";
        if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
            isNeg = true;

        long res = divHelper(abs(dividend), 0, abs(divisor), isNeg);
        // cout << "RES: " << res << " " << isNeg << endl;
        res = isNeg ? -res : res;

        if (res > INT_MAX)
            return INT_MAX;
        else if (res < INT_MIN)
            return INT_MIN;
        return res;
    }
};