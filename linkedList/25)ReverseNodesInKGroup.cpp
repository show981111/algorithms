/**
 * We can reverse linked list with 2 ways.
 *
 * 1. Recursion, reversing from the middle(swapping values)
 * 2. Weaving. Keep prev, cur, next and perform fliping
 */
class Solution
{
public:
    typedef pair<ListNode *, ListNode *> Range;
    // reverse and return the new head
    ListNode *reverse(ListNode *cur, int k)
    {
        if (cur == nullptr || k <= 1)
            return cur;
        ListNode *prev = nullptr;
        ListNode *next = cur->next;
        // Weaving reverse.
        // X     Y    Z
        // prev  cur  next
        // X <- Y <- Z
        while (k--)
        {
            cur->next = prev;
            prev = cur;
            cur = next;
            if (next)
                next = next->next;
        }

        return prev;
    }
    ListNode *reverseKGroupHelper(ListNode *cur, int curIndex, int k)
    {
        if (cur == nullptr)
            return nullptr;
        ListNode *iter = cur;
        int i = 0;
        // decide whether we have to reverse list or not.
        // need to know if we have more than "k" nodes. Traverse inevitable
        while (iter && i < k)
        {
            i++;
            iter = iter->next;
        }
        if (i < k)
            return cur;
        // else reverse

        ListNode *h = reverse(cur, k);
        // reverse the rest as the rule and take the head as a next ptr
        cur->next = reverseKGroupHelper(iter, 1, k); // 1-index

        return h;
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        return reverseKGroupHelper(head, 1, k);
    }
};