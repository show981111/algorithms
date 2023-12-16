/**
 * Tricky part was, how to differentiate Empty & Full?
 *
 * If we start head = tail = 0, EMPTY should be H == T.
 *      Push elem will assign value of arr[T] then T++.
 *      Then, if we push full size number of elems, then FUll is also H == T.
 * 1) Let H = T = -1 in the beginning and when equeuing the item increment then assign value.
 *      -> Still, cannot differentiate Empty & only one element exists.
 *          EX) Index: 0 1 2
 *              Value: 5
 *                    H/T
 *
 * 2) Make Tail refers to the Empty Slot right after the last element!!!
 *    Make empty H == T and Full (T+1) % cap == H (one index difference)
 *    How? Introduce one extra space;
 *    Starting from H = T = 0. If H == T: empty.
 *    Equeue by arr[T] = value ; T = (T + 1)%cap.
 *    If (T + 1)%cap == head? -> Since Tail should refer empty slot always, this means queue is full!
 */

class MyCircularQueue
{
public:
    vector<int> arr;
    int cap, head, tail;
    MyCircularQueue(int k)
    {
        arr.resize(k + 1);
        cap = k + 1;
        head = 0;
        tail = 0;
    }

    bool enQueue(int value)
    {
        if (isFull())
            return false;
        arr[tail] = value;
        tail = (tail + 1) % cap;
        return true;
    }

    bool deQueue()
    {
        if (isEmpty())
            return false;
        head = (head + 1) % cap;
        return true;
    }

    int Front()
    {
        if (isEmpty())
            return -1;
        return arr[head];
    }

    int Rear()
    {
        if (isEmpty())
            return -1;
        return arr[(cap + tail - 1) % cap];
    }

    int size()
    {
        if (head < tail)
            return (tail - head) % cap;
        else
            return (cap + tail - head) % cap;
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