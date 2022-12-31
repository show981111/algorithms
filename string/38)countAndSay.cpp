/**
 * @brief Iterative
 *
 */
class Solution
{
public:
    string helper(string n)
    {
        string res;
        int curIndex = 0;

        while (curIndex < n.size())
        {
            int curCount = 0;
            char curNum = n[curIndex];

            int pos = curIndex;
            while (pos < n.size() && n[pos] == curNum)
            {
                curCount++;
                pos++;
            }
            curIndex = pos;
            res.push_back(curCount + '0');
            res.push_back(curNum);
        }
        return res;
    }
    string countAndSay(int n)
    {
        if (n == 1)
            return "1";

        string res = "1";
        for (int i = 2; i <= n; i++)
        {
            res = helper(res);
        }

        return res;
    }
};

/**
 * @brief Recursive
 *
 */

class Solution
{
public:
    string helper(int n)
    {
        if (n == 1)
            return "1";

        string prevRes = helper(n - 1);
        string res = "";
        int curIndex = 0;
        while (curIndex < prevRes.size())
        {
            char curNum = prevRes[curIndex];
            int count = 0;
            while (curIndex < prevRes.size() && prevRes[curIndex] == curNum)
            {
                curIndex++;
                count++;
            }
            res += to_string(count);
            res += curNum;
        }
        return res;
    }
    string countAndSay(int n)
    {
        return helper(n);
    }
};