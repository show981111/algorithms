/**
What we want to do is compare i th elem, and N - ith elem 
using recursive... how?

We move forward the cur pointer(which is a parameter),
and also we move forward the return value(go above mid!)

page.230 crack coding interview

*/
class Solution {
public:
    ListNode* helper(ListNode* cur, int length, bool &ans){
        if(length == 0){
            return cur;
        }else if(length == 1){
            return cur->next;
        }
        ListNode* comp = helper(cur->next, length -2, ans);
        if(ans && comp->val == cur->val)
            ans = true;
        else
            ans = false;
        return comp->next;
    }
    bool isPalindrome(ListNode* head) {
        if(!head)
            return true;
        bool ans = true;
        ListNode* cur = head;
        int length = 0;
        while(cur != nullptr){
            length++;
            cur= cur->next;
        }
        helper(head, length, ans);
        return ans;
    }
};