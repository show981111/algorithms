#include <stack>
using namespace std;
/*
Push : O(1) and Pop : O(n)
*/
class MyQueue
{
public:
    MyQueue()
    {
    }

    void push(int x)
    {
        if (mainStack.empty())
        {
            front = x;
        }
        mainStack.push(x);
    }

    int pop()
    {
        while (!mainStack.empty())
        {
            int curTop = mainStack.top();
            mainStack.pop();
            temp.push(curTop);
        }
        int oldTop = temp.top();
        temp.pop();
        if (temp.empty())
            return oldTop;

        front = temp.top();
        while (!temp.empty())
        {
            int curTop = temp.top();
            temp.pop();
            mainStack.push(curTop);
        }
        return oldTop;
    }

    int peek()
    {
        return front;
    }

    bool empty()
    {
        if (mainStack.empty())
            return true;
        else
            return false;
    }

private:
    int front;
    stack<int> mainStack;
    stack<int> temp; //contain top elem of mainStack. Use as a contaienr when pop                       //elem
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */