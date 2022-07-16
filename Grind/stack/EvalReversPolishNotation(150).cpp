/**
 * @brief Using a Function Type in CPP!!
 * We create a Map using a function type!
 *
 */

class Solution
{
public:
    unordered_map<string, function<int(int, int)>> fmap = {
        {"+", [](int a, int b)
         { return a + b; }},
        {"-", [](int a, int b)
         { return a - b; }},
        {"*", [](int a, int b)
         { return a * b; }},
        {"/", [](int a, int b)
         { return a / b; }},
    };
    int evalRPN(vector<string> &tokens)
    {
        stack<int> nums;
        for (string &op : tokens)
        {
            if (fmap.find(op) != fmap.end())
            {
                int sec = nums.top();
                nums.pop();
                int fir = nums.top();
                nums.pop();
                int res = fmap[op](fir, sec);
                nums.push(res);
            }
            else
            {
                nums.push(stoi(op));
            }
        }

        return nums.top();
    }
};