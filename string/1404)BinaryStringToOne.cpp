class Solution
{
public:
    void add(string &n)
    {
        for (auto it = n.rbegin(); it != n.rend(); ++it)
        {
            if (*it == '0')
            {
                *it = '1';
                return;
            }
            else
            {
                *it = '0';
            }
        }
        n = "1" + n;
    }
    int step(string &n, int steps)
    {
        if (n == "1")
            return steps;
        if (n.back() == '0')
        {                 // even
            n.pop_back(); // divide
            return step(n, steps + 1);
        }
        else
        {
            add(n);
            return step(n, steps + 1);
        }
    }
    int numSteps(string s)
    {
        return step(s, 0);
    }
};
