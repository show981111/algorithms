/**
 * @brief
 * Key Idea => using fast/slow + temporary head
 *
 */

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *tempHead = new ListNode;
        tempHead->next = head;
        ListNode *fast = tempHead, *slow = tempHead;
        n++; // since we need to know the previous pointer of the node we will delete!
        while (n--)
        {
            fast = fast->next;
        }
        while (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return tempHead->next;
    }
};

/**
 * Or if we know the size, we can do lots of stuff for linked list!
 */

class Solution
{
public:
    ListNode *deleteAt(ListNode *head, int targetIndex)
    {
        ListNode *cur = head;
        ListNode *prev = cur;
        int idx = 0;
        while (idx < targetIndex)
        {
            prev = cur;
            cur = cur->next;
            idx++;
        }
        ListNode *victim, *newHead = head;
        if (targetIndex == 0)
        {
            newHead = head->next;
            victim = head;
        }
        else
        {
            victim = cur;
            prev->next = cur->next;
        }
        delete victim;
        return newHead;
    }
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        int length = 0;
        ListNode *cur = head;

        while (cur != nullptr)
        {
            cur = cur->next;
            length++;
        }
        int deleteIndex = length - n;
        return deleteAt(head, deleteIndex);
    }
};