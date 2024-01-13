/**
 * Reversing from the middle!
 *
 * If we are trying to reverse from the outside, it gets tricky because we have to save all nodes in the middle to access the node on the other side.
 * If we are reversing from the middle, we can just reverse, go back one node for first half, go forward one node for second half and perform swap.
 *      Then, we dont have to store all nodes (only needs node in the first half since we have to move backwards) because in second half, we only need next node to swap.
 *
 * Using this, we can design a recursive function:
 *      Why recursive? At each step we just doing the same thing: Swapping the value with the node in the other half
 *
 * Desinging the recursive function:
 *      Since we need an access to the node in the other half, we return the node.
 *      Base case would be when we hit the mid point.
 *          We should start returning the next node to swap.
 *          EX) 1 2 | 3 4 5 6 7 | 8 (reverse 3 ~ 7)
 *              1 2 3 4 [5] 6 7 8 (Reached the mid point, start returning. Here return 6)
 *              1 2 3 [4] 5 6 7 8 (At 4, we got 6 as a returned node. We swap value and return the 6->next, which is 7)
 *              1 2 [3] 6 5 4 7 8 (At 3 we got 7 as a returned node. We swap value and return the 7->next, which is 8 )
 *              1 [2] 7 6 5 4 3 8 (2 < left(3), so just dont do anything and return)
 */
class Solution
{
public:
    ListNode *helper(ListNode *cur, int curIndex, int left, int right)
    {
        if (cur == nullptr)
            return cur;
        if (curIndex == (left + right) / 2)
        {
            if ((right - left + 1) % 2 == 0)
            { // even number of nodes. Swap with next node and return next->next so that the previous node can swap with correct node
                swap(cur->val, cur->next->val);
                return cur->next->next;
            }
            else
                return cur->next; // odd number of nodes, just return next node
        }
        ListNode *temp = helper(cur->next, curIndex + 1, left, right); // get the node on the other half
        if (curIndex >= left && temp != nullptr)
        {
            swap(temp->val, cur->val); // swap value (reverse)
            return temp->next;         // return the next node on the other half
        }
        else
            return nullptr;
    }
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        helper(head, 1, left, right);
        return head;
    }
};