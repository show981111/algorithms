/**
 * A great way of thinking recursive in Linked list.
 *
 * Get the mid node and start from the middle!
 * <1 <2 <3 4> 5> 6>
 *
 * From the middle, we enlarge the range. Each recursive call will give the
 * next pair on the other side! ex) 5, 6
 */
class Solution
{
    /*
    1 2 3 4 5 6
    1 6 2 5 3 4
    Recursive approach just like we did for palindrom.
    We can re-order from the middle of the list
    EX) 1 2 <3 4> 5 6
    LIST: <3 4>
    1 <2 3 4 5> 6
    LIST: <2 5> -> <3 4>
    <1 2 3 4 5 6>
    LIST: <1 6> -> <2 5> -> <3 4>
    Need to return the next pair node.
    */
public:
    ListNode *reorder(ListNode *cur, int length, int idx)
    {
        if (cur == nullptr)
            return nullptr;
        if (length % 2 == 0 && idx == (length / 2 - 1))
        {
            ListNode *nextPair = cur->next->next;
            cur->next->next = nullptr;
            return nextPair;
        }
        else if (length % 2 == 1 && idx == length / 2)
        {
            ListNode *nextPair = cur->next;
            cur->next = nullptr;
            return nextPair;
        }
        ListNode *connectTo = cur->next;
        ListNode *pair = reorder(cur->next, length, idx + 1);
        ListNode *nextPair = pair->next;
        cur->next = pair;
        pair->next = connectTo;
        return nextPair;
    }
    void reorderList(ListNode *head)
    {
        int l = 0;
        ListNode *cur = head;
        while (cur)
        {
            cur = cur->next;
            l++;
        }
        reorder(head, l, 0);
    }
};

/**
 * @brief Reverse order? -> Stack! or Actually reverse it!
 *
 */
class Solution
{
public:
    void reorderList(ListNode *head)
    {
        if (!head || !head->next)
            return;

        vector<ListNode *> st;
        ListNode *mid = head;
        ListNode *cur = head;

        while (cur && cur->next)
        {
            cur = cur->next->next;
            mid = mid->next; // mid is round up
        }
        while (mid)
        {
            st.push_back(mid);
            mid = mid->next;
        }
        cur = head;

        while (!st.empty())
        {
            ListNode *tempNext = cur->next; // 3
            if (tempNext == st.back())
            {
                break;
            }
            cur->next = st.back();
            st.back()->next = tempNext;
            cur = tempNext;
            st.pop_back();
        }
        cur->next->next = nullptr;
    }
};

/**
 * Less Space!
 * Reverse order in Linked List -> why not just actually reverse it!
 */
class Solution
{
public:
    void reorderList(ListNode *head)
    {
        if (!head || !head->next)
            return;

        ListNode *mid = head;
        ListNode *cur = head;

        // finding mid
        while (cur && cur->next)
        {
            cur = cur->next->next;
            mid = mid->next; // mid is round up
        }
        ListNode *prev = mid;

        // reversing
        cur = mid->next;
        while (cur)
        {
            ListNode *temp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = temp;
        }
        mid->next = nullptr;

        // merging
        ListNode *front = head;
        ListNode *back = prev;
        while (front != mid)
        {
            ListNode *frontNext = front->next;
            ListNode *backNext = back->next;
            front->next = back;
            back->next = frontNext;
            front = frontNext;
            back = backNext;
        }
        mid->next = nullptr;
    }
};

/**
 * @brief
 *
 */