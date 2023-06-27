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