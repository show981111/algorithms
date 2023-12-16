/**
 * 16 / 3 =?
 * 16 = 2^2 *3 + 2^0*3 + 1 = (2^2 + 2^0)*3 + 1 => quotient = 2^2 + 2^0 = 5, remainder 1
 *
 * Recursive
 */

class Solution
{
public:
    int getMaxPowerOfTwo(long a, long b)
    {
        long twos = b;
        int power = -1;
        while (twos <= a)
        {
            ++power;
            twos = twos << 1;
        }
        return power;
    }

    void div(long a, long b, long &quo)
    {
        int power = getMaxPowerOfTwo(a, b);
        if (power == -1)
            return;
        // cout << "p: " << power << endl;

        long coef = ((long)1 << power);
        // cout << coef << endl;
        quo += coef;
        if (quo > (long)INT_MAX + 1)
        {
            return;
        }
        a -= coef * b;
        div(a, b, quo);
    }
    int divide(int dividend, int divisor)
    {
        int sign = (dividend >= 0 && divisor >= 0) || (dividend <= 0 && divisor <= 0) ? 1 : -1;
        long a = abs(dividend);
        long b = abs(divisor);
        long quo = 0;
        div(a, b, quo);

        if (quo * sign > INT_MAX)
            return INT_MAX;
        else if (quo * sign < INT_MIN)
            return INT_MIN;
        return quo * sign;
    }
};

/**
 * Iterative.
 *
 * Go up until it gets bigger than dividend, then goes down by dividing and subtracting.
 */

int divide(int dividend, int divisor)
{
    int sign = (dividend >= 0 && divisor >= 0) || (dividend <= 0 && divisor <= 0) ? 1 : -1;
    long a = abs(dividend);
    long b = abs(divisor);
    // div(a,b,quo);
    if (a < b)
        return 0;

    long twos = b;
    long quo = 0;
    int power = 0;
    while (twos <= a)
    {
        twos = twos << 1;
        ++power; // hit max
    }
    while (a > 0)
    {
        while (twos > a)
        {
            twos = twos >> 1;
            power--;
        } // twos <= a
        if (power < 0)
        {
            break;
        }
        quo += ((long)1 << power);
        if (quo > (long)INT_MAX + 1)
            break;
        a -= twos;
    }

    if (quo * sign > INT_MAX)
        return INT_MAX;
    else if (quo * sign < INT_MIN)
        return INT_MIN;
    return quo * sign;
}