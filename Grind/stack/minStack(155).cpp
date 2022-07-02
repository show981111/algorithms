/**
 * @brief Two Stack
 * we have a stack which stacks smaller elements.
 * Even though we pop min(), we still have a next min in mins because
 * next min should be pushed earlier than the current min.
 * ex) push 7 4 ,
 * min stack [7 4] => 7 is bigger than 4 and it came before 4
 * ex2) push -4 5 7
 * min stack [-4] => since -4 is the smallest and the bottom of the stack,
 * popping elements doesn't change the min
 */

class MinStack
{
private:
    stack<int> s1;
    stack<int> mins;

public:
    void push(int x)
    {
        s1.push(x);
        if (mins.empty() || x <= getMin())
            mins.push(x);
    }
    void pop()
    {
        if (s1.top() == getMin())
            mins.pop();
        s1.pop();
    }
    int top()
    {
        return s1.top();
    }
    int getMin()
    {
        return mins.top();
    }
};

/**
 * @brief Using a pair
 * We keep recording the current min per each stage(each element)
 * In Current stage(when this element is pushed), min element is!
 * We record this information as a pair!
 */

class MinStack
{
private:
    stack<pair<int, int>> st;
    //<value, curMin>
public:
    void push(int x)
    {
        if (st.empty())
            st.push({x, x});
        else
        {
            st.push({x, min(x, st.top().second)});
        }
    }
    void pop()
    {
        st.pop();
    }
    int top()
    {
        return st.top().first;
    }
    int getMin()
    {
        return st.top().second;
    }
};
