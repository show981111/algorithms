/**
 * Managing index might be confusing!
 */
class Solution
{
public:
    ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2)
    {
        ListNode *cur = list1;
        int idx = 0;
        ListNode *l2tail = list2;
        while (l2tail->next != nullptr)
            l2tail = l2tail->next;
        while (idx <= b)
        {
            if (idx == a - 1)
            {
                // a-1_th node, need to connect to the head of list2
                ListNode *temp = cur->next;
                cur->next = list2;
                cur = temp; // keep proceeding the old list to connect the tail of list 2 to b_th node
            }
            else if (idx == b)
            { // connect the end of list2 with b_th node
                l2tail->next = cur->next;
            }
            else
            {
                cur = cur->next;
            }
            idx++;
        }

        return list1;
    }
};