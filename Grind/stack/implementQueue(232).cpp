/**
 * Amortized O(1) for pop and peek,
 * since all elements are moved to pushStack to popStack once!
 * popping N elements => O(n), so popping 1 element => O(1)
 * push : O(1)
 */

#include <stack>

class MyQueue
{
public:
    MyQueue()
    {
    }

    void push(int x)
    {
        pushStack.push(x);
    }

    int pop()
    {
        fillPopStack();
        int f = popStack.top();
        popStack.pop();
        return f;
    }

    int peek()
    {
        fillPopStack();
        return popStack.top();
    }

    bool empty()
    {
        return pushStack.empty() && popStack.empty();
    }

private:
    stack<int> pushStack;
    stack<int> popStack;

    void fillPopStack()
    {
        if (popStack.empty())
        {
            while (!pushStack.empty())
            {
                popStack.push(pushStack.top());
                pushStack.pop();
            }
        }
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */