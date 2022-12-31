/**
https://leetcode.com/problems/divide-two-integers/discuss/1516367/Complete-Thinking-Process-or-Intuitive-Explanation-or-All-rules-followed-or-C%2B%2B-code

Use power of 2 to get quotient faster!
58 = (2^3 + 2^1 + 2^0) * 5 + 3                // --- (I)
58 = [(2^3 * 5) + (2^1 * 5) + (2^0 * 5)] + 3  // --- (II)
keep subtracting... 
*/

class Solution {
public:
    int divide(int dividend, int divisor) {
        bool isNeg = (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0) ? true : false;
        dividend = abs(dividend); 
        divisor = abs(divisor);
        
        long quotient = 0;
        long div = divisor;
        long mul = 1;

        while((div << 1) <= dividend){
            div = div << 1;
            mul = mul << 1;
            if(!isNeg && mul >= INT_MAX) 
                return INT_MAX;
            if(isNeg && -mul <= INT_MIN)
                return INT_MIN;
        }
        while(dividend >= 0 && div > 0){
            if(dividend - div >= 0)
            {
                dividend -= div;
                quotient += mul;
            }
            div = div >> 1;
            mul = mul >> 1;
        }
        return isNeg? -quotient : quotient;
    }
};