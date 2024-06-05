class Solution
{
public:
    /*
    S S N N S S S N
    A A B B C C D E = D ^ E

    Set bits in D ^ E are the bit position where D and E are different. Let's choose rightmost bit
    that are different. Using this, we can divide the entire array into two groups also spliting D from E!
    (Since we know that that position bit is different from D and E).
    Now, in each group, we exactly have 2*n + 1 elements since other than D and E, all elements exist as pair (two elements). Thus, if we XORing each group, we can get D and E each.

    EX) Right most set: (A ^ A ^ C ^ C) ^ D = D Right most not set: (B ^ B) ^ E = E
    */
    vector<int> singleNumber(vector<int> &nums)
    {
        long xorAll = 0;
        for (int &n : nums)
            xorAll ^= n;

        int rightMostSet = xorAll & (-xorAll);
        /*
        // If we don't want to use Long for xorAll. We use long since -INT_MIN is above ing range!
        // MAX int is 2^31 - 1 since it is total 32 bits with one sigh bits.
        // MIN int is -2^31
        int power = 0;
        int rightMostSet = 1;
        while(power <= 31){
            if((rightMostSet & xorAll) == 0){
                rightMostSet = rightMostSet << 1;
                power++;
            }else
                break;
        }
        */
        int a = 0, b = 0;
        for (int &n : nums)
        {
            if ((n & rightMostSet) > 0)
            {
                a ^= n;
            }
            else
            {
                b ^= n;
            }
        }
        return {a, b};
    }
};
