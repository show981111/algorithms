class Solution
{
public:
    /*
    "(1+(4+5+2)-3)+(6+8)"
    => 1 4 5 + 2 + + 3 - 6 8 + +
    3 - 1 * 2 + 5

    3 1 2 * - 5
    Its num: just concat to string
    Its Op: add to opStack. If existing op is high priority, pop them. If not, just push
    If Par: Just push par to op. If we see closing par, pop operands until we see the closing par!
    https://todaycode.tistory.com/73

    Tricky part is dealing with unary operation.
    If previous word was a number, then the operation is binary.
    But if prev was not a number, then the operation is unary -> so add 0!
    */

    string inFixToPostFix(string &s)
    {
        stack<char> opStack;
        string postFix = "";
        bool prevIsNum = false;
        for (int i = 0; i < s.size();)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            else if (isdigit(s[i]))
            {
                int start = i;
                while (isdigit(s[i]))
                {
                    i++;
                }
                postFix += s.substr(start, i - start);
                postFix.push_back(' ');
                prevIsNum = true;
            }
            else if (s[i] != '(' && s[i] != ')')
            {                                                    // op
                while (!opStack.empty() && opStack.top() != '(') // only - and +, no need to check priority
                {
                    postFix.push_back(opStack.top());
                    postFix.push_back(' ');
                    opStack.pop();
                }
                if (prevIsNum == false)
                { // add 0 cuz it is a unary operation
                    postFix += "0 ";
                }
                opStack.push(s[i]);
                i++;
                prevIsNum = false;
            }
            else
            { // par
                if (s[i] == '(')
                {
                    opStack.push('(');
                }
                else
                {
                    while (opStack.top() != '(')
                    {
                        postFix.push_back(opStack.top());
                        postFix.push_back(' ');
                        opStack.pop();
                    }
                    opStack.pop(); // pop '('
                }
                i++;
                // prevIsNum = false;
            }
        }
        while (!opStack.empty())
        {
            postFix.push_back(opStack.top());
            postFix.push_back(' ');
            opStack.pop();
        }
        return postFix;
    }
    int doOp(int fir, int sec, string op)
    {
        if (op == "+")
        {
            return fir + sec;
        }
        else
        {
            return fir - sec;
        }
    }
    int calculate(string s)
    {
        // infix To PostFix
        // ex) 3 * (1 - 2) => 3 1 2 - *
        // 3 - 1 * 2 => 3 1 2 * -
        string pf = inFixToPostFix(s);
        // cout << pf << endl;
        istringstream iss(pf);

        stack<int> numStack;
        string w;
        while (iss >> w)
        {
            if (w == "+" || w == "-")
            {
                int sec = numStack.top();
                numStack.pop();
                int fir = 0;
                if (!numStack.empty())
                {
                    fir = numStack.top();
                    numStack.pop();
                }
                numStack.push(doOp(fir, sec, w));
                // cout << fir << " " << w << " " << sec << endl;
            }
            else
            {
                numStack.push(stoi(w));
            }
        }

        return numStack.top();
    }
};

/**
 * We only have + and -. Use this fact to make a simple version!
 * Unless there is a paranthesis, operation is sequential since + and - have the same priority.
 * Now, If there is a paranthesis, store the current result to stack,
 *                                 compute the expression inside the paranthesis,
 *                                 when parenthesis closes, pop the prev result from the stack and add prevResult and current expression's value.
 *
 * String -> Integer.
 * "123"  -> 123
 * Do not need to add them in reverse order.
 * Just do,
 *      num = num * 10 + digit;
 * Shift the current result to left as we move!
 */

class Solution
{
public:
    struct Num
    {
        int num;
        int sign;
    };
    int calculate(string s)
    {
        int ans = 0;
        int sign = 1;
        stack<Num> st;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
                continue;
            if (s[i] == '(')
            {
                st.push({ans, sign});
                ans = 0;
                sign = 1; // reset and add it later
            }
            else if (s[i] == ')')
            {
                Num &n = st.top();
                ans = n.num + n.sign * ans;
                // current result is stored in ans.
                // n.num stores the result from before paranthesis opens
                // n.sign contains the sign of whole paranthesis
                // update ans!
                st.pop();
            }
            else if (s[i] == '+')
            {
                sign = +1;
            }
            else if (s[i] == '-')
            {
                sign = -1;
            }
            else
            { // number
                int number = 0;
                while (isdigit(s[i]))
                { // will enter while 100% cuz s[i] is digit
                    number = number * 10 + (s[i] - '0');
                    i++;
                }
                i--; // subtract to offset for-loop's i++
                ans += sign * number;
            }
        }
        return ans;
    }
};