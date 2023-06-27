// bottom up O(1) space
class Solution
{
public:
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        else if (n == 1 || n == 2)
            return 1;
        // t_n+3 = t_n + t_n+1 + t_n+2
        // total 4 terms needed
        int n0 = 0, n1 = 1, n2 = 1, n3;

        for (int i = 3; i <= n; i++)
        {
            n3 = n0 + n1 + n2;
            n0 = n1;
            n1 = n2;
            n2 = n3;
        }

        return n3;
    }
};

// top down O(n) == O(depth of tree) space
class Solution
{
public:
    vector<int> memo;
    int helper(int n)
    {
        if (n == 0)
            return 0;
        else if (n == 1 || n == 2)
            return 1;

        if (memo[n] != 0)
            return memo[n];
        else
            return memo[n] = helper(n - 1) + helper(n - 2) + helper(n - 3);
    }
    int tribonacci(int n)
    {
        memo.resize(n + 1);
        return helper(n);
    }
};