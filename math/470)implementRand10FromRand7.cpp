/**
 * Just like binary representation,
 * we can generate rand_N^x with rand_N
 */
class Solution
{
public:
    int rand10()
    {
        // 10^1 * (0 ~ 9) + 10^0 * (0 ~ 9) => 0 ~ 99 equaly distribute
        // So if we add 1 at the end, 10^1 * (0 ~ 9) + 10^0 * (0 ~ 9) + 1 => 1 ~ 100 !
        // Thus, 10*(rand10 - 1) + rand10 - 1 + 1 = rand100
        // Like This,
        // 7*(rand7 - 1) + rand7 - 1 + 1 = rand49
        // 0 ~ 48 : 0: 0,10,20,30,40, 1 : 1,11,21,31,41 , ... , 9 : 9, 19, 29, 39, -> only 4 nines! not equal!
        int randZeroTo48;
        do
        {
            randZeroTo48 = 7 * (rand7() - 1) + rand7() - 1;
        } while (randZeroTo48 % 10 == 0); // to equally distribute 0 ~ 9, cut-off values above 40!
        return randZeroTo48 % 10;
    }
};

/**
 * Failed version
 * Be careful of Mod!
 */

class Solution
{
public:
    int rand10()
    {
        // 1 ~ 49 : 0: 10,20,30,40, 1 : 1,11,21,31,41 , ... , 9 : 9, 19, 29, 39,
        int rand49;
        do
        {
            rand49 = 7 * (rand7() - 1) + (rand7() - 1) + 1;
        } while (rand49 % 10 == 0); // to equaly distribute 0 ~ 9, cut-off values above 40!
        return rand49 % 10;         // result only 1 ~ 9 -> rand9! not rand10!
    }
};