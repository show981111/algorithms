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
class Solution {
public:
    ListNode* helper(ListNode* l1, ListNode* l2, int &carry){
        if(l1 == nullptr && l2 == nullptr)
            return nullptr;
        ListNode* next = helper(l1->next, l2->next, carry);
        int val = l1->val + l2->val + carry;
        int digit = val % 10;
        carry = val / 10;
        ListNode* cur = new ListNode(digit);
        cur->next = next;
        return cur;       
    }
    ListNode* addPadding(ListNode* l){
        ListNode* newHead = new ListNode(0);
        newHead->next = l;
        return newHead;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* cur1 = l1, *cur2 = l2;
        while(cur1 != nullptr || cur2 != nullptr){
            if(cur1 == nullptr && cur2 != nullptr){
                l1 = addPadding(l1);
                cur2 = cur2->next;
            }else if(cur1 != nullptr && cur2 == nullptr){
                l2 = addPadding(l2);
                cur1 = cur1->next;
            }else{
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
        }
        int carry = 0;
        ListNode* res = helper(l1,l2, carry);
        if(carry > 0){
            ListNode* temp = new ListNode(carry);
            temp->next = res;
            res = temp;
        }
        return res;
    }
};