/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *middleNode(ListNode *head)
    {
        int sizeOfList = 0;
        ListNode *cur = head;
        while (cur != nullptr)
        {
            sizeOfList++;
            cur = cur->next;
        }
        int middleIndex = sizeOfList / 2;
        cout << middleIndex;
        while (middleIndex--)
        {
            head = head->next;
        }
        return head;
    }
};