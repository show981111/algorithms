/**
 * @brief Prev, cur pattern.
 * Prev = cur;
 * cur = cur->next;
 *
 */
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *prev = nullptr, *cur = head;
        if (head == nullptr)
            return nullptr;

        while (cur != nullptr)
        {
            prev = cur;
            cur = cur->next;
            while (prev != nullptr && cur != nullptr && prev->val == cur->val)
            {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
        }
        return head;
    }
};