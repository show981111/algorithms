/**
 * Definition for singly-linked list.
 */
#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        if (list1 == nullptr && list2 == nullptr)
            return list1;

        ListNode *cur = new ListNode();
        ListNode *dummyHead = cur;
        while (1)
        {
            if (list1 == nullptr && list2 == nullptr)
                break;

            if (list1 == nullptr)
            {
                cur->next = list2;
                list2 = list2->next;
            }
            else if (list2 == nullptr)
            {
                cur->next = list1;
                list1 = list1->next;
            }
            else
            {
                if (list1->val < list2->val)
                {
                    cur->next = list1;
                    list1 = list1->next;
                }
                else
                {
                    cur->next = list2;
                    list2 = list2->next;
                }
            } // set head
            cur = cur->next;
        }
        ListNode *realHead = dummyHead->next;
        delete dummyHead;
        return realHead;
    }
};