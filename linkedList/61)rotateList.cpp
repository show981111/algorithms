/**
 * @brief Brute Force
 * Shift one step until we shift K % N amount
 *
 */

class Solution
{
public:
    ListNode *forward(ListNode *head, ListNode *cur)
    {
        if (cur->next == nullptr)
        {
            return head;
        }
        return cur->next;
    }
    void shift(ListNode *head)
    { // O(N)
        ListNode *cur = head;
        int prev = cur->val;
        while (cur != nullptr)
        {
            ListNode *nextNode = forward(head, cur);
            int tempCurVal = nextNode->val;
            nextNode->val = prev;
            prev = tempCurVal;
            cur = cur->next;
        }
    }
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == nullptr)
            return head;
        int N = 0;
        ListNode *cur = head;
        while (cur)
        {
            N++;
            cur = cur->next;
        }
        cur = head;
        int rotateNum = k % N;
        for (int i = 0; i < rotateNum; i++)
        {
            shift(head);
        }
        // O(N*K)
        return head;
    }
};
/**
 * @brief Rotating...
 * Could be interpreted as disconnect head and
 * put it next to the tail!
 * Or
 * Disconnect tail and put before head!
 *
 * O(N) approach!
 */
class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == nullptr)
            return head;
        int N = 0;
        ListNode *cur = head;
        ListNode *tail = cur;
        while (cur)
        {
            N++;
            tail = cur;
            cur = cur->next;
        } // O(N) to get length
        int rotateNum = k % N;
        cur = head;
        if (rotateNum != 0) // O(N-K) to reconnect the list!
        {
            for (int i = 0; i < N - rotateNum; i++)
            {
                tail->next = cur;  // we take head and connect next to tail, cur becomes tail!
                cur = cur->next;   // forward cur(head)
                tail = tail->next; // forward tail!
            }
        }
        tail->next = nullptr; // to make the list not circular!
        return cur;           // this is a new head!
    }
};