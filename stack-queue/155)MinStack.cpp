class MinStack
{
private:
    stack<pair<int, int>> st;
    // Invariant:
    // Min value will stay the same even though we pop
    // elements, cuz those elems are !above! the min.
    // -> Min value will be popped later(below) than current elem.
    // Min value might change if we pop the min value.
    // -> record the min at each level of stack.
public:
    void push(int x)
    {
        if (st.empty())
        {
            st.push(make_pair(x, x));
        }
        else
        {
            st.push(make_pair(x, min(st.top().second, x)));
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
