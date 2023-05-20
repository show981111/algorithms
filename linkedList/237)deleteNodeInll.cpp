class Solution
{
public:
    void deleteNode(ListNode *node)
    {
        // have no access to the previous node
        // shift elems after that node, and delete the last elem!
        ListNode *target = node;
        ListNode *newTail = node;
        while (target->next)
        {
            target->val = target->next->val;
            newTail = target;
            target = target->next;
        }

        delete target;
        newTail->next = nullptr;
    }
};