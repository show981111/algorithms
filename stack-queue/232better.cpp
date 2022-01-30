#include <stack>

using namespace std;
/*
Push : O(1) and Pop : Amortized O(1)
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
            mainStackBottom = x;
        }
        mainStack.push(x);
    }

    int pop()
    {
        if (temp.empty())
        {
            while (!mainStack.empty())
            {
                int curTop = mainStack.top();
                mainStack.pop();
                temp.push(curTop);
            }
        }
        int oldTop = temp.top();
        temp.pop();

        return oldTop;
    }

    int peek()
    {
        if (temp.empty())
            return mainStackBottom;
        else
            return temp.top();
    }

    bool empty()
    {
        if (mainStack.empty() && temp.empty())
            return true;
        else
            return false;
    }

private:
    int mainStackBottom;
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