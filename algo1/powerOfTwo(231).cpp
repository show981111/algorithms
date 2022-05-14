class Solution
{
public:
    // if we do n - 1, then rightmost 1 becomes 0 and after that,
    // it becomes all 1. so if it is not a power of two, then
    // there must be the part that is the same as "n", so it won't be 0
    // but if it is power of two, then rightmost 1 is the first 1 from the left
    // ex) 10000000 so every digit is different from n - 1 so result is 0
    bool isPowerOfTwo(int n)
    {
        long x = (long)n - 1;
        if (n == 0)
            return false;
        if ((n & x) == 0)
            return true;
        return false;
    }
};