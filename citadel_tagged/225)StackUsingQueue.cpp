/**
 * Pop/Top: O(N)
 * Push: O(1)
 */

class MyStack
{
public:
    queue<int> main;
    queue<int> sub;
    MyStack()
    {
    }

    void push(int x)
    {
        main.push(x);
    }
    void rebalance()
    {
        while (!sub.empty())
        {
            main.push(sub.front());
            sub.pop();
        }
    }

    int pop()
    {
        int t = -1;
        while (!main.empty())
        {
            if (main.size() == 1)
                t = main.front();
            else
                sub.push(main.front());
            main.pop();
        }
        rebalance();
        return t;
    }

    int top()
    {
        int t = -1;
        while (!main.empty())
        {
            if (main.size() == 1)
                t = main.front();
            sub.push(main.front());
            main.pop();
        }
        rebalance();
        return t;
    }

    bool empty()
    {
        return main.empty() && sub.empty();
    }
};

/**
 * One Queue
 *
 * Push : O(N)
 * Top/Pop : O(1)
 *
 * Each time we push, we rotate queue so that pushed elem is at the front.
 * Since at each push, we rotate queue we can maintain the overall ordering of reverse order.
 * EX) push 1, 2, 3
 *
 * 1
 * 1,2-> 2,1
 * 2,1,3-> 3,2,1
 */

class MyStack
{
public:
    queue<int> q;
    MyStack()
    {
    }

    void push(int x)
    {
        int qSize = q.size();
        q.push(x);
        for (int i = 0; i < qSize; ++i)
        {
            q.push(q.front());
            q.pop();
        }
    }

    int pop()
    {
        int t = q.front();
        q.pop();
        return t;
    }

    int top()
    {
        return q.front();
    }

    bool empty()
    {
        return q.empty();
    }
};
