/**
 * prefix + map.
 *
 * Can look up the prefix I am looking for in O(1)!
 */

class Solution
{
public:
    int pivotInteger(int n)
    {
        unordered_map<int, int> prefix;
        int s = 0;
        for (int i = 1; i <= n; i++)
        {
            s += i;
            prefix[s] = i;
            // cout << s << " " << i << endl;
        }
        for (int i = 1; i <= n; i++)
        {
            int ss = s + i;
            if (ss % 2 == 0 && prefix.count(ss / 2) > 0 && prefix[ss / 2] == i)
            {
                return i;
            }
        }

        return -1;
    }
};

/**
 * MATH
 */

class Solution
{
public:
    int pivotInteger(int n)
    {
        int prefix = 0;
        int suffix = (n + 1) * n / 2;

        for (int i = 1; i <= n; i++)
        {
            prefix += i;
            if (prefix == suffix)
                return i;
            suffix -= i;
        }
        return -1;
    }
};