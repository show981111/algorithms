class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t res = 0;
        int shift = 31;

        while (n > 0)
        {
            int lastDigit = n % 2;
            n = n >> 1;
            res += (lastDigit << shift);
            shift--;
        }
        return res;
    }
};