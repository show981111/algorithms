/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // start "K" step late from the shorter list
        // move 1 step at each time
        // if there is a poin where A == B, then intersect
        int lengA = 0;
        int lengB = 0;
        ListNode* curA = headA;
        ListNode* curB = headB;
        
        while(curA){
            lengA++;
            curA = curA->next;
        }
        while(curB){
            lengB++;
            curB = curB->next;
        }
        int diff = abs(lengA-lengB);
        while(diff > 0){
            if(lengA > lengB)
                headA = headA->next;
            else
                headB = headB->next;
            diff--;
        }
        while(headA != nullptr && headA != headB){
            headA = headA->next;
            headB = headB->next;
        }
        
        return headA;
    }
};