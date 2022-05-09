/**
 * Recursive => Stack
 * Stack : reverse something!
 */
class Solution
{
public:
    ListNode *reverseHelper(ListNode *cur)
    {
        if (cur->next == nullptr)
            return cur;

        ListNode *next = cur->next;
        ListNode *head = reverseHelper(next);
        next->next = cur;
        return head;
    }
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr)
            return head;
        ListNode *res = reverseHelper(head);
        head->next = nullptr;
        return res;
    }
};