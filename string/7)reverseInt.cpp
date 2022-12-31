class Solution
{
public:
    bool isOutOfRange(string &a, string &limit)
    {
        if (a.length() > limit.length())
            return true;
        else if (a.length() < limit.length())
        {
            return false;
        }
        else
        {
            for (int i = 0; i < a.length(); i++)
            {
                if (a[i] - '0' > limit[i] - '0')
                {
                    return true;
                }
                else if (a[i] - '0' < limit[i] - '0')
                {
                    return false;
                }
            }
        }
        return false;
    }
    int reverse(int x)
    {
        if (x == 0)
            return x;
        string limit = to_string(INT_MAX);
        bool pos = true;
        if (x < 0)
        {
            pos = false;
            limit = to_string(INT_MIN);
            limit.erase(limit.begin());
        }
        string ans = "";
        while (x != 0)
        {
            int digit = abs(x % 10);
            x /= 10;

            if (ans.empty() && digit == 0)
                continue;
            ans.push_back(digit + '0');
            if (isOutOfRange(ans, limit))
            {
                return 0;
            }
        }
        if (pos)
            return stoi(ans);
        else
            return -stoi(ans);
    }
};