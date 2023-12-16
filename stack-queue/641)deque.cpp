/**
 * Head refers to the first item.
 * Tail refers to the empty slot right after the last item.
 */

class MyCircularDeque
{
public:
    vector<int> arr;
    int cap;
    int head, tail;
    MyCircularDeque(int k) : cap(k + 1), head(0), tail(0)
    {
        arr.resize(cap);
    }

    /*
       0 1 2 3
           T H
    */
    bool insertFront(int value)
    {
        if (isFull())
            return false;
        head = (cap + head - 1) % cap; // Since head refers to the first item, move head first
        arr[head] = value;             // then assign
        return true;
    }

    bool insertLast(int value)
    {
        if (isFull())
            return false;
        arr[tail] = value;       // Since tail refers to the empty space right next to the last item, assign
        tail = (tail + 1) % cap; // and move
        return true;
    }

    bool deleteFront()
    {
        if (isEmpty())
            return false;
        head = (head + 1) % cap;
        return true;
    }

    bool deleteLast()
    {
        if (isEmpty())
            return false;
        tail = (cap + tail - 1) % cap;
        return true;
    }

    int getFront()
    {
        if (isEmpty())
            return -1;
        return arr[head];
    }

    int getRear()
    {
        if (isEmpty())
            return -1;
        return arr[(cap + tail - 1) % cap];
    }

    bool isEmpty()
    {
        return head == tail;
    }

    bool isFull()
    {
        if ((tail + 1) % cap == head)
            return true;
        return false;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */