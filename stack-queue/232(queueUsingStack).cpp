/*
THOUGHT FLOW:
    STACK: only one place of popping and pusing
    QUEUE: popping from the back, pushing to front (2 places)
    -> need at least two stack
    should pop the bottom element!

TC:
Push : O(1) and Pop : Worst O(n)
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
        if (popStack.empty())
            pushToPopStack();
        int val = popStack.top();
        popStack.pop();
        return val;
    }

    int peek()
    {
        if (popStack.empty())
            pushToPopStack();
        return popStack.top();
    }

    bool empty()
    {
        return popStack.empty() && pushStack.empty();
    }

private:
    stack<int> popStack;  // [ 4 3 2 8 7 6 5
    stack<int> pushStack; // [

    void pushToPopStack()
    {
        while (!pushStack.empty())
        {
            popStack.push(pushStack.top());
            pushStack.pop();
        }
    }
};

/*
Tracking the Bottom Elem ->
push/pop/peek: Amortized O(1)
Each elem is moved to popStack only once!
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
        if (pushStack.empty())
            bottomOfPushStack = x;
        pushStack.push(x);
    }

    int pop()
    {
        if (popStack.empty())
            pushToPopStack();
        int val = popStack.top();
        popStack.pop();
        return val;
    }

    int peek()
    {
        if (popStack.empty())
            return bottomOfPushStack;
        else
            return popStack.top();
    }

    bool empty()
    {
        return popStack.empty() && pushStack.empty();
    }

private:
    // STACK: only one place of popping and pusing
    // QUEUE: popping from the back, pushing to front (2 places)
    // -> need at least two stack
    // should pop the bottom element!
    stack<int> popStack; // [ 4 3 2 8 7 6 5
    stack<int> pushStack;
    int bottomOfPushStack;

    void pushToPopStack()
    {
        while (!pushStack.empty())
        {
            popStack.push(pushStack.top());
            pushStack.pop();
        }
    }
};
