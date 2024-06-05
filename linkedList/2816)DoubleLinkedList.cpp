class Solution
{
    /**
     * Key to solving LinkedList is design a recursive function.
     * When writing a recursive function, think about
     * Passing the information downwards(parameter)/upwards(return value)
     */
public:
    int doubleItHelper(ListNode *cur)
    {
        if (cur == nullptr)
        {
            return 0;
        }
        int ret = doubleItHelper(cur->next);
        int d = 2 * cur->val + ret;
        int q = d / 10;
        cur->val = d % 10;
        return q;
    }
    ListNode *doubleIt(ListNode *head)
    {
        int r = doubleItHelper(head);
        if (r > 0)
        {
            ListNode *newHead = new ListNode(r);
            newHead->next = head;
            return newHead;
        }
        return head;
    }
};
