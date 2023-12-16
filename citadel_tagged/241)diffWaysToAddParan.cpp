/**
 * Recursion
 *
 * Calculation is based on operator.
 *
 * https://leetcode.com/problems/different-ways-to-add-parentheses/solutions/1294189/easy-solution-faster-than-100-explained-with-diagrams/
 * Different way of calculating depends on which operator we calculate first.
 *
 * ex) 2 - 1 + 5, if we do - first, (2-1) + 5. If we do + first, 2 - (1+5)
 *
 * When we evaluate a string expression, there could be multiple values (depending on result),
 * so when we "Merge" the results, we should merge all result values.
 *
 * T(exp) = T(left) op T(right)
 *
 * For + recursion! => sometimes this might be easy! dont have to use purley one another.
 * We can mix it!
 *
 * Start from bare string, then later optimize!
 */

class Solution
{
public:
    int doOp(int x, int y, char op)
    {
        if (op == '-')
        {
            return x - y;
        }
        else if (op == '*')
        {
            return x * y;
        }
        else if (op == '+')
        {
            return x + y;
        }
        return -1;
    }
    vector<int> solve(string exp)
    {
        vector<int> res;
        bool pureDigit = true;
        for (int i = 0; i < exp.size(); i++)
        {
            if (!isdigit(exp[i]))
            {
                pureDigit = false;
                vector<int> left = solve(exp.substr(0, i));
                vector<int> right = solve(exp.substr(i + 1));

                for (int l = 0; l < left.size(); l++)
                {
                    for (int r = 0; r < right.size(); r++)
                    {
                        res.push_back(doOp(left[l], right[r], exp[i]));
                    }
                }
            }
        }
        if (pureDigit)
        {
            res.push_back(stoi(exp));
        }
        return res;
    }
    vector<int> diffWaysToCompute(string expression)
    {
        return solve(expression);
    }
};

/**
 * Avoid frequent substr using indexing!
 */

class Solution
{
public:
    int doOp(int x, int y, char op)
    {
        if (op == '-')
        {
            return x - y;
        }
        else if (op == '*')
        {
            return x * y;
        }
        else if (op == '+')
        {
            return x + y;
        }
        return -1;
    }
    vector<int> solve(int start, int end, string &exp)
    {
        vector<int> res;
        bool pureDigit = true;
        for (int i = start; i < end; i++)
        {
            if (!isdigit(exp[i]))
            {
                pureDigit = false;
                vector<int> left = solve(start, i, exp);
                vector<int> right = solve(i + 1, end, exp);

                for (int l = 0; l < left.size(); l++)
                {
                    for (int r = 0; r < right.size(); r++)
                    {
                        res.push_back(doOp(left[l], right[r], exp[i]));
                    }
                }
            }
        }
        if (pureDigit)
        {
            res.push_back(stoi(exp.substr(start, end - start)));
        }
        return res;
    }
    vector<int> diffWaysToCompute(string expression)
    {
        return solve(0, expression.size(), expression);
    }
};