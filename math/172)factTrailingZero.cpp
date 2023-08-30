/**
 * @brief Question is.. how to count 2s and 5s in n! = 1 * 2 * ... * n
 * We can do this in log, by counting how many multipes are in N.
 * N / d gives us how many multiples of d's are in 1 ~ N.
 * ex) 10 / 2 = 5, there are 5 multipes of 2.
 * So, using this, we should count multiples of 2, 2*2, 2*2*2, ... to get twos,
 *                                              5, 5*5, 5*5*5, ... to get fives!
 *
 * EX) 125 ->
 * 125 / 5 = 25 multiples of 5. -> CNT = 25
 * 125 / 25 = 5 multiples of 25. -> CNT = 5 + 25 cuz, 25 contains two 5
 * 125 / 125 = 1 multiples of 125 -> CNT = 1 + 5 + 25 cuz 125 contains three 5's and two fives are counted before.
 */

class Solution
{
public:
    int getCnt(int n, int d)
    { // log_d since d grows exponentially
        int cnt = 0;
        int mul = d;
        while (n >= d)
        { // same as n / d != 0
            cnt += n / d;
            d *= mul;
        }
        return cnt;
    }
    int trailingZeroes(int n)
    {
        int twos = getCnt(n, 2);
        int fives = getCnt(n, 5);

        return min(twos, fives);
    }
    // 1 2 3 4 5  6 7 8 9 10
    //   2.  2.   2.  2.  2 5
    //       2.       2
    //                2
};