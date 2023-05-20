/**
 * @brief LinkedList + recursion
 * Easy to make a mistake
 * A) consider when carry is non-zero when l1 and l2 both reach the end ex) 9 + 1 = 10
 * B) Cannot early stop even though carry == 0. we should traverse to the end of both numbers
 * C) do not have to worry about the length difference because two numbers are in reverse order
 * D) reduce redundancy using extra variables! (l1Val, l2Val)
 *
 */

/**
 * @brief Recursive version
 * Return value = what we want!
 * pass information we need in the future call as a parameter!
 */
class Solution
{
public:
    ListNode *add(ListNode *l1, ListNode *l2, int c)
    {
        // want to return head.
        ListNode *curHead;
        int sum = c;
        int d;
        if (l1 && l2)
        {
            sum += l1->val + l2->val;
            l1 = l1->next;
            l2 = l2->next;
        }
        else if (l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        else if (l2)
        {
            sum += l2->val;
            l2 = l2->next;
        }
        else
        {
            if (c > 0)
            {
                return new ListNode(c);
            }
            else
                return nullptr;
        }

        d = sum % 10;
        c = sum / 10;
        curHead = new ListNode(d);
        curHead->next = add(l1, l2, c);
        return curHead;
    }
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {

        return add(l1, l2, 0);
    }
};