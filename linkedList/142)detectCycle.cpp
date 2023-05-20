/*
Floyd's cycle detection algo
OR
Use Hashmap to store and find duplicate!
*/
class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast = head, *slow = head;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                break;
        }

        if (fast == nullptr || fast->next == nullptr)
            return nullptr;

        fast = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};