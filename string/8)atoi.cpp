class Solution
{
public:
    int myAtoi(string s)
    {
        int num = 0;
        int sign = 1;
        bool digitFaced = false;
        for (int i = 0; i < s.size(); i++)
        {
            if (!digitFaced)
            {
                if (s[i] == ' ')
                    continue;
                else if (isdigit(s[i]))
                { // First digit
                    digitFaced = true;
                    num += sign * (s[i] - '0');
                }
                else if (s[i] == '-')
                {
                    digitFaced = true;
                    sign = -1;
                }
                else if (s[i] == '+')
                {
                    // num is already positive
                    digitFaced = true;
                }
                else
                {
                    return num;
                }
            }
            else
            {
                if (isdigit(s[i]))
                { // next Digit
                    long temp = (long)num * 10 + sign * (s[i] - '0');
                    if (temp <= INT_MIN)
                    {
                        return INT_MIN;
                    }
                    else if (temp >= INT_MAX)
                        return INT_MAX;
                    num = temp;
                }
                else
                { // faced non digit
                    return num;
                }
            }
        }
        return num;
    }
};