/**
 * @brief Calculator using a simple stack!
 *
 * Solving Infix notation(중위표기) without any parenthesis
 *  => just add/sub/mul/div sequentially
 *     Do not need any stack. just one integer and one variable to deal with operation
 *
 * When we have parenthesis... => we need to save current result and
 * should come back after we solve parenthesis first.
 * => So we need something to store current result.
 * Queue? Stack?
 * Key of caculating is that we need to use the most recent one when
 * we have multiple parenthesis.
 * ex) 1 + (2 + (3+ 4)) => 3+4 and, 2 + (3+4), and 1 + the rest.
 * So we should use stack.
 *
 */

class Solution
{
public:
    int calculate(string s)
    {
        stack<pair<int, int>> state; // ans , sign
        int ans = 0;
        int sign = 1;
        int i = 0;

        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (c == ' ')
                continue;
            else if (c == '(')
            {
                state.push({ans, sign});
                ans = 0;
                sign = 1;
            }
            else if (c == ')')
            {
                pair<int, int> mostRecentRes = state.top();
                state.pop();
                ans = mostRecentRes.first + (mostRecentRes.second * ans);
                sign = 1;
            }
            else if (c == '+')
            {
                sign = +1;
            }
            else if (c == '-')
            {
                sign = -1;
            }
            else
            {
                int num = 0;
                while (i < s.size() && isdigit(c))
                {
                    num = (num * 10 + (c - '0'));
                    c = s[++i];
                }
                i--;
                ans = ans + (sign * num);
            }
        }

        return ans;
    }
};