/**
 * @brief String -> int
 *
 * 1) Use stack.
 *      while(!st.empty())
 *      {
 *          ans += mul
 *          mum *= 10;
 *      }
 * 2) add sequentially
 *      while(){
 *          result = result*10 + cur;
 *      }
 */

class Solution
{
public:
    int myAtoi(string s)
    {
        stack<int> st;
        int step = 1;
        char sign = '+';
        for (auto ch : s)
        {
            if (step == 1 && ch == ' ')
                continue;
            if (step == 1 && (ch == '-' || ch == '+'))
            {
                sign = ch;
                step++;
            }
            else if (!isdigit(ch))
            {
                break;
            }
            if (isdigit(ch))
            {
                step = 3;
                if (st.empty() && ch == '0')
                    continue;
                st.push(ch - '0');
            }
        }
        long ans = 0;
        long mul = sign == '+' ? 1 : -1;
        while (!st.empty())
        {
            int i = st.top();
            ans += mul * i;
            if (ans > INT_MAX || mul > INT_MAX)
            {
                ans = INT_MAX;
                // cout << INT_MAX << endl;
                break;
            }
            else if (ans < INT_MIN || mul < INT_MIN)
            {
                ans = INT_MIN;
                break;
            }
            mul *= 10;
            st.pop();
        }
        return ans;
    }
};