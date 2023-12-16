class Solution
{
public:
    int getPriority(char x)
    {
        if (x == '*' || x == '/')
            return 1;
        return 0;
    }
    int doOp(char op, int f, int s)
    {
        if (op == '+')
            return f + s;
        if (op == '-')
            return f - s;
        if (op == '*')
            return f * s;
        if (op == '/')
            return f / s;
        return -1;
    }
    void calculate(stack<char> &ops, stack<int> &nums)
    {
        char curOp = ops.top();
        ops.pop();
        int sec = nums.top();
        nums.pop();
        int fir = nums.top();
        nums.pop();
        nums.push(doOp(curOp, fir, sec));
    }
    int calculate(string s)
    {
        istringstream in(s);
        int n;
        char op;
        stack<char> ops;
        stack<int> nums;

        while (in >> n)
        {
            nums.push(n);
            if (in >> op)
            {
                while (!ops.empty() && getPriority(ops.top()) >= getPriority(op))
                {
                    // if previous operation's priority is higher, perform operation
                    calculate(ops, nums);
                    // cout << nums.top() << " ";
                }
                ops.push(op);
            }
            else
            {
                // end of string
                while (!ops.empty())
                {
                    // if previous operation's priority is higher, perform operation
                    calculate(ops, nums);
                    // cout << nums.top() << " ";
                }
            }
        }
        return nums.top();
    }
};