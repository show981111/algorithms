/**
 * Reverse list by stitching (reverse two nodes at a time)!
 *
 * Keep three pointers.
 * Front -> Back
 * As we proceed Front and Back, we have temp to store the Back's next
 */

ListNode *reverseList(ListNode *head)
{
    if (head == nullptr)
        return nullptr;

    ListNode *front = nullptr;
    ListNode *back = head;

    while (back != nullptr)
    {
        ListNode *temp = back->next;
        back->next = front;
        front = back;
        back = temp;
    }
    return front;
}

/**
Reverse List by modify next node's next to current node.
*/
class Solution
{
public:
    ListNode *reverseHelper(ListNode *cur, ListNode *&newHead)
    {
        if (cur == nullptr)
            return nullptr;
        ListNode *next = reverseHelper(cur->next, newHead);
        if (next != nullptr)
        {
            next->next = cur;
        }
        else
        {
            newHead = cur;
        }
        return cur;
    }
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return head;
        ListNode *newHead = nullptr;
        ListNode *tail = reverseHelper(head, newHead);
        tail->next = nullptr; // this is necessary, because tail->next is set to wrong one.(2nd elem in the list)
        return newHead;
    }
};
/**
Reverse Node by swapping values
Idea is from 234)palindrome!
*/
class Solution
{
public:
    ListNode *helper(ListNode *cur, int length)
    {
        if (length == 0)
        {
            return cur;
        }
        else if (length == 1)
        {
            return cur->next;
        }
        ListNode *comp = helper(cur->next, length - 2);
        swap(cur->val, comp->val);
        return comp->next;
    }
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return head;
        ListNode *cur = head;
        int length = 0;
        while (cur != nullptr)
        {
            length++;
            cur = cur->next;
        }
        helper(head, length);
        return head;
    }
};