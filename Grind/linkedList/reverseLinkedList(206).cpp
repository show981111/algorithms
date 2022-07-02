/**
 * @brief Reverse!! => stack! => recursive!
 *
 * Recursive version
 * We should proceeed to the end first before we make a change,
 * unless we can get a infinit cycle since we are chaing the "next" ptr.
 * We can change this code a lil to return the head
 */

class Solution
{
public:
    // this code returns head of reversed Linked List
    // ListNode* reverseHelper(ListNode* cur){
    //     if(cur->next == nullptr)
    //         return cur;

    //     ListNode* next = cur->next;
    //     ListNode* head = reverseHelper(next);
    //     next->next = cur;
    //     return head;
    // }
    ListNode *reverseHelper(ListNode *head, ListNode *&newHead)
    {
        if (head->next == nullptr)
        {
            newHead = head;
            return head;
        }
        ListNode *prev = reverseHelper(head->next, newHead);
        prev->next = head;
        return head;
    }
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return nullptr;
        ListNode *newHead;
        ListNode *tail = reverseHelper(head, newHead);
        tail->next = nullptr;
        return newHead;
    }
};

/**
 * @brief Iterative version(using a stack)
 *
 */
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return nullptr;
        ListNode *newHead;
        stack<ListNode *> st;
        while (head != nullptr)
        {
            st.push(head);
            head = head->next;
        }
        newHead = st.top();
        ListNode *cur = newHead;
        st.pop();
        while (!st.empty())
        {
            cur->next = st.top();
            st.pop();
            cur = cur->next;
        }
        cur->next = nullptr;
        return newHead;
    }
};