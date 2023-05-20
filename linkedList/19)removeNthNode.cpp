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