/**
What we want to do is compare i th elem, and N - ith elem
using recursive... how?

We move forward the cur pointer(which is a parameter),
and also we move forward the return value(go above mid!)

page.230 crack coding interview

*/
class Solution
{
public:
    ListNode *helper(ListNode *cur, int length, bool &ans)
    {
        if (length == 0)
        {
            return cur;
        }
        else if (length == 1)
        {
            return cur->next;
        }
        ListNode *comp = helper(cur->next, length - 2, ans);
        if (ans && comp->val == cur->val)
            ans = true;
        else
            ans = false;
        return comp->next;
    }
    bool isPalindrome(ListNode *head)
    {
        if (!head)
            return true;
        bool ans = true;
        ListNode *cur = head;
        int length = 0;
        while (cur != nullptr)
        {
            length++;
            cur = cur->next;
        }
        helper(head, length, ans);
        return ans;
    }
};

/*
Another recursive version O(N), O(N)
What we need? Boolean value about isPalindrome
We should compare last elem of left and first elem of right (reverse direction)

Reverse... we need to store the value of left!
Calling recursive function -> save current node!
We can forward Left Node without changing the current recursive step's left node.

What we need from the next step? Boolean result, forwarded Right value
(since we have current left, we need forwarded Right => pass by ref!)
*/
class Solution
{
public:
    bool checker(ListNode *left, ListNode *&right, ListNode *mid)
    {
        if (left->next == mid)
        {
            bool res = left->val == right->val;
            right = right->next;
            return res;
        }
        else
        {
            bool res = checker(left->next, right, mid);
            bool comp = left->val == right->val;
            right = right->next;
            return comp && res;
        }
    }
    bool isPalindrome(ListNode *head)
    {
        ListNode *mid = head;
        ListNode *fast = head;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            mid = mid->next;
        }
        ListNode *left = head;
        ListNode *right;
        if (fast == nullptr)
        { // length is even
            right = mid;
        }
        else
        {
            right = mid->next;
        }
        if (mid == left)
            return true;
        return checker(left, right, mid);
    }
};

/**
 * @brief Reverse Linked List
 * CHALLENGE: We need to compare left and right in reverse order!
 * Can we do this in-place?
 * oh,, we can reverse the order of linked list in-place!
 * Why dont we reverse the order of left?
 * Reversing needs 3 pointers
 * lead : iterating list
 * prevLead : save prev value of lead
 * left : Head of the reversed linked list (prev value of prevLead)
 *
 * left -> prevLead -> lead
 * [left <- prevLead]
 * [left = prevLead]
 */

class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        ListNode *mid = head;
        ListNode *fast = head;
        ListNode *prevMid;
        ListNode *left = nullptr;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            prevMid = mid;
            mid = mid->next;
            prevMid->next = left;
            left = prevMid;
        }
        ListNode *right;
        if (fast == nullptr) // length is even
        {
            right = mid;
        }
        else
        {
            right = mid->next;
        }

        while (right)
        {
            if (right->val != left->val)
                return false;
            right = right->next;
            left = left->next;
        }
        return true;
    }
};