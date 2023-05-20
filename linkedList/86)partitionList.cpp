/*
Think in-place? -> use extra space? -> increase time complexity?
using temporary head is really useful for dealing with edge cases!
The advantage of linked list is we have a full control on that node(memory)!
=> just move the node without deep-copying
*/

// O(N), O(N) solution
// we make the copy node for each value.. why not just move that node?
class Solution
{
public:
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *leftHead = new ListNode();
        ListNode *rightHead = new ListNode();

        ListNode *l = leftHead, *r = rightHead;
        ListNode *cur = head;
        while (cur)
        {
            if (cur->val < x)
            {
                l->next = new ListNode(cur->val);
                l = l->next;
            }
            else
            {
                r->next = new ListNode(cur->val);
                r = r->next;
            }
            cur = cur->next;
        }

        l->next = rightHead->next;
        return leftHead->next;
    }
};
/*
O(1) space solution!
The advantage of linked list is we have a full control on that node(memory)!
Do not deep copy the node, we can just move it!
*/
class Solution
{
public:
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *leftHead = new ListNode();
        ListNode *rightHead = new ListNode();

        ListNode *l = leftHead, *r = rightHead;
        ListNode *cur = head;
        while (cur)
        {
            if (cur->val < x)
            {
                l->next = cur;
                l = l->next;
            }
            else
            {
                r->next = cur;
                r = r->next;
            }
            cur = cur->next;
        }
        r->next = nullptr;

        l->next = rightHead->next;
        return leftHead->next;
    }
};