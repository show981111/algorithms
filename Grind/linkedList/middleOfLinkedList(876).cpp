/**
 * @brief Getting the middle of Linked List
 *
 * Using the concept of finding cycle
 *
 * Two pointers
 * Slow, Fast. Fast goes twice as Slow. If Fast reaches the end,
 * then Slow should at the middle of the list because the distance
 * traveled by Fast is twice as Slow
 */

class Solution
{
public:
    ListNode *middleNode(ListNode *head)
    {
        ListNode *slow = head;
        while (head && head->next)
        {
            head = head->next->next;
            slow = slow->next;
        }
        return slow;
    }
};