/**
 * @brief LinkedList + recursion
 * Easy to make a mistake
 * A) consider when carry is non-zero when l1 and l2 both reach the end ex) 9 + 1 = 10
 * B) Cannot early stop even though carry == 0. we should traverse to the end of both numbers
 * C) do not have to worry about the length difference because two numbers are in reverse order
 * D) reduce redundancy using extra variables! (l1Val, l2Val)
 *
 */
class Solution
{
public:
    ListNode *add(ListNode *l1, ListNode *l2, int carry)
    {
        if (l1 == nullptr && l2 == nullptr && carry == 0)
            return nullptr;

        int l1Val = 0;
        int l2Val = 0;

        if (l1 != nullptr)
        {
            l1Val = l1->val;
            l1 = l1->next;
        }
        if (l2 != nullptr)
        {
            l2Val = l2->val;
            l2 = l2->next;
        }

        unsigned int sum = l1Val + l2Val + carry;
        unsigned int digit = sum % 10;
        unsigned int newCarry = sum / 10;
        ListNode *cur = new ListNode(digit);
        cur->next = add(l1, l2, newCarry);
        return cur;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        return add(l1, l2, 0);
    }
};