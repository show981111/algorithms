/**
 * @brief Cycle Detection
 * A) using a Hashset
 *      - store numbers it visited, if it visit the number that we already visited, cycle!
 *      - Time : O(n), Space : O(n)
 * B) Floyd's cycle detection algorithm (Two pointers)
 *      - Fast pointers(move 2steps), Slow pointers(move 1step)
 *      - If it meets at the end, there is no cycle
 *      - If it doesn't meet at the end, then there is a cycle
 *      - Time : O(n), Space : O(1)
 * Why they always meet if there is a cycle?
 *      Suppose fast pointer is "k" steps behind slow pointer
 *      A) if f pointer is 1 step behind, then it will meet after 1 move.
 *      Now, T(N) = 1 + T(N-1) (T(N) is moves needed to f and s meet)
 *      Why? Every each move, the interval between f and s reduced by 1.
 *      because f goes 2, s goes 1. Thus, T(N) = 1 + T(N-1)
 * Now, after they meet, send one pointer to the starting point.
 * Porceed each pointer one step at a time. Then they will meet at the entrypoint of cycle!!
 *
 * https://www.youtube.com/watch?v=PvrxZaH_eZ4&ab_channel=Insidecode
 */

class Solution
{
public:
    int next(int x)
    {
        int sum = 0;
        while (x != 0)
        {
            int digit = x % 10;
            sum += digit * digit;
            x /= 10;
        }
        return sum;
    }
    bool isHappy(int n)
    {
        int slow = next(n);
        int fast = next(next(n));

        while (fast != slow) // until they meet!
        {
            slow = next(slow);
            fast = next(next(fast));
        }

        return fast == 1;
    }
};