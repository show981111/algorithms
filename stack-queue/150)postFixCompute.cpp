class Solution
{
public:
    bool isOp(string &t)
    {
        if (t == "+" || t == "-" || t == "*" || t == "/")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int doOp(int fir, int sec, string &t)
    {
        if (t == "+")
        {
            return fir + sec;
        }
        else if (t == "-")
        {
            return fir - sec;
        }
        else if (t == "*")
        {
            return fir * sec;
        }
        else if (t == "/")
        {
            return fir / sec;
        }
        else
        {
            return -1;
        }
    }
    int evalRPN(vector<string> &tokens)
    {
        stack<int> nums;
        for (auto &t : tokens)
        {
            if (isOp(t))
            {
                int sec = nums.top();
                nums.pop();
                int fir = nums.top();
                nums.pop();
                nums.push(doOp(fir, sec, t));
            }
            else
            {
                // numbers
                nums.push(stoi(t));
            }
        }
        return nums.top();
    }
};