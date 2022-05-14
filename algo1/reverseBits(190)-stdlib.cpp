/**
 * @brief Using a bitset https://en.cppreference.com/w/cpp/utility/bitset/bitset
 * the constructor accepts both string and number
 * bitset<SIZE> bits(number or string)
 * THree key member function!
 * to_ulong(), to_string(), to_ullong()
 */

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        bitset<32> bts(n);
        string bits = bts.to_string();
        reverse(bits.begin(), bits.end());
        return bitset<32>(bits).to_ulong();
    }
};