/**
 * Classic Stack problem for Calculator!
 *
 * We keep operands & operator stack.
 * Kinda like monotonic stack, we perform calculation if the operator
 * that are lower than current top is coming in. (until the current operator can be the highest one!)
 * Then the operator stack will be increasing order ex) + , *
 */
class Solution
{
public:
    int doOp(int a, int b, char op)
    {
        if (op == '+')
        {
            return a + b;
        }
        else if (op == '-')
        {
            return a - b;
        }
        else if (op == '*')
        {
            return a * b;
        }
        else if (op == '/')
        {
            return a / b;
        }
        assert(false);
    }
    bool isOp(char x)
    {
        return x == '+' || x == '-' || x == '*' || x == '/';
    }
    int getPriority(char op)
    {
        if (op == '+' || op == '-')
            return 0;
        if (op == '*' || op == '/')
            return 1;
        return -1;
    }
    void doCal(vector<int> &operands, char op)
    {
        int second = operands.back();
        operands.pop_back();
        int first = operands.back();
        operands.pop_back();
        operands.push_back(doOp(first, second, op));
    }
    int calculate(string s)
    {
        vector<int> operands;
        stack<char> ops;
        int i = 0;

        string num = "";
        while (i < s.size())
        {
            if (s[i] != ' ' && !isOp(s[i]))
                num.push_back(s[i]);
            else if (isOp(s[i]))
            {
                operands.push_back(stoi(num));
                num.clear();
                while (!ops.empty() && getPriority(ops.top()) >= getPriority(s[i])) // perform operation for all ops which has a higher priority
                {
                    doCal(operands, ops.top());
                    ops.pop();
                }
                ops.push(s[i]);
            }
            i++;
        }
        if (num.size() > 0)
            operands.push_back(stoi(num));
        while (!ops.empty())
        {
            doCal(operands, ops.top());
            ops.pop();
        }
        return operands.back();
    }
};