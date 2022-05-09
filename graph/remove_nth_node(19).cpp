/**
 * Two Pointer + sliding window!
 *
 */
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *prev = head;
        ListNode *target = head;
        while (target)
        {
            ListNode *targetTemp = target;
            ListNode *prevTemp = prev;
            int i = 0;
            for (; i < n; i++)
            {
                prevTemp = targetTemp;
                targetTemp = targetTemp->next;
            }
            if (targetTemp == nullptr && i == n)
            {
                if (prev == target)
                {
                    return head->next;
                }
                if (target == nullptr)
                    return nullptr;
                prev->next = target->next;
                return head;
            }
            prev = target;
            target = target->next;
        }
        return nullptr;
    }
};