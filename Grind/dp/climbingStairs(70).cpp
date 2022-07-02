class Solution
{
public:
    int climbStairs(int n)
    {
        int cur = 1, prev = 1, prevPrev = 1;

        for (int i = 2; i <= n; i++)
        {
            cur = prev + prevPrev;
            prevPrev = prev;
            prev = cur;
        }
        return cur;
    }
};