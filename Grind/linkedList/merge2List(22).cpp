/**
 * @brief LinkedList
 * It is convenient to have dummyHead!!
 *
 */

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *dummyHead = new ListNode();
        ListNode *head = dummyHead;
        while (list1 != nullptr || list2 != nullptr)
        {
            if (list1 == nullptr)
            {
                dummyHead->next = list2;
                list2 = list2->next;
            }
            else if (list2 == nullptr)
            {
                dummyHead->next = list1;
                list1 = list1->next;
            }
            else
            {
                if (list1->val > list2->val)
                {
                    dummyHead->next = list2;
                    list2 = list2->next;
                }
                else
                {
                    dummyHead->next = list1;
                    list1 = list1->next;
                }
            }
            dummyHead = dummyHead->next;
        }

        return head->next;
    }
};