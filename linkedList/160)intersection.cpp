/*
Knowing the length really helps!

Think about.. what if I know the length?

*/
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        // start "K" step late from the shorter list
        // move 1 step at each time
        // if there is a poin where A == B, then intersect
        int lengA = 0;
        int lengB = 0;
        ListNode *curA = headA;
        ListNode *curB = headB;

        while (curA)
        {
            lengA++;
            curA = curA->next;
        }
        while (curB)
        {
            lengB++;
            curB = curB->next;
        }
        int diff = abs(lengA - lengB);
        while (diff > 0)
        {
            if (lengA > lengB)
                headA = headA->next;
            else
                headB = headB->next;
            diff--;
        }
        while (headA != nullptr && headA != headB)
        {
            headA = headA->next;
            headB = headB->next;
        }

        return headA;
    }
};
/**
 * If we need to know the difference, we can just run simultaniously!
 */
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        // might use hashMap -> O(A+B), but O(A) space
        // What if we know both length?
        // Preceding nodes of longer list cannot be an intersection

        ListNode *aCur = headA, *bCur = headB;
        while (aCur || bCur)
        {
            if (aCur && bCur)
            {
                aCur = aCur->next;
                bCur = bCur->next;
            }
            else if (aCur)
            {
                aCur = aCur->next;
                headA = headA->next; // this head cannot be an intersection
            }
            else if (bCur)
            {
                bCur = bCur->next;
                headB = headB->next;
            }
        }
        while (headA && headA != headB)
        {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
};