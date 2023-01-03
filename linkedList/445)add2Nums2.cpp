/**
 * @brief Recursion
 * Adding numbers => always be careful of carry!!!
 *
 * 먼저 자릿수를 맞춰주는것이 중요, 왜냐면 리스트가 reverse가 아니므로...
 * recursion 을 쓰면 자릿수 차이만큼 스킵을 할 방법이 읍다!
 * => ADD PADDING! -> might waste space
 *
 * Recursion -> how to use the next digit's calculation?
 *           -> how to use the information of next iteration?
 *            ** pass that result as a return value!!
 *               The result bubbles up as a return value, and at each step, we can use it.
 *               Return values are stored as a function stack!
 *
 */
class Solution
{
public:
    void addPadding(ListNode *&head)
    {
        ListNode *newHead = new ListNode(0);
        newHead->next = head;
        head = newHead;
    }
    ListNode *add(ListNode *num1, ListNode *num2, int &carry)
    {
        if (num1 == nullptr && num2 == nullptr)
            return nullptr;
        ListNode *nextDigit = add(num1->next, num2->next, carry);
        int sum = num1->val + num2->val + carry;
        int digit = sum % 10;
        carry = sum / 10;
        ListNode *cur = new ListNode(digit);
        cur->next = nextDigit;
        return cur;
    }
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *l1Head = l1, *l2Head = l2;
        while (l1 != nullptr || l2 != nullptr)
        {
            if (l1 == nullptr)
            {
                addPadding(l1Head);
                l2 = l2->next;
            }
            else if (l2 == nullptr)
            {
                addPadding(l2Head);
                l1 = l1->next;
            }
            else
            {
                l1 = l1->next;
                l2 = l2->next;
            }
        }
        int carry = 0;
        ListNode *result = add(l1Head, l2Head, carry);
        if (carry > 0)
        {
            ListNode *newResult = new ListNode(carry);
            newResult->next = result;
            return newResult;
        }
        return result;
    }
};

/**
 * @brief Skipping instead of adding a padding!
 *
 */
class Solution
{
public:
    ListNode *add(ListNode *longerList, ListNode *shorterList, int &carry, int lengDiff)
    {
        if (longerList == nullptr && shorterList == nullptr)
            return nullptr;
        int sum;
        ListNode *nextDigit;
        if (lengDiff > 0)
        {
            lengDiff--;
            nextDigit = add(longerList->next, shorterList, carry, lengDiff);
            sum = longerList->val + carry;
        }
        else
        {
            nextDigit = add(longerList->next, shorterList->next, carry, lengDiff);
            sum = longerList->val + shorterList->val + carry;
        }
        int digit = sum % 10;
        carry = sum / 10;
        ListNode *cur = new ListNode(digit);
        cur->next = nextDigit;
        return cur;
    }
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *l1Head = l1, *l2Head = l2;
        ListNode *longerList, *shorterList;
        int lengthDiff = 0;
        bool isl1Long = true;
        while (l1 != nullptr || l2 != nullptr)
        {
            if (l1 == nullptr)
            {
                lengthDiff++;
                l2 = l2->next;
                isl1Long = false;
            }
            else if (l2 == nullptr)
            {
                lengthDiff++;
                l1 = l1->next;
            }
            else
            {
                l1 = l1->next;
                l2 = l2->next;
            }
        }
        if (isl1Long)
        {
            longerList = l1Head;
            shorterList = l2Head;
        }
        else
        {
            longerList = l2Head;
            shorterList = l1Head;
        }
        int carry = 0;
        ListNode *result = add(longerList, shorterList, carry, lengthDiff);
        if (carry > 0)
        {
            ListNode *newResult = new ListNode(carry);
            newResult->next = result;
            return newResult;
        }
        return result;
    }
};