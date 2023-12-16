/**
 * Using a Median
 *
 * If we use slow/fast ptr we get ceil(median)!
 */
class Solution
{
public:
    ListNode *helper(ListNode *front, ListNode *back, bool &ans, bool isEven)
    {
        if (front == back)
        {
            // cout << ans << " ";
            if (isEven)
                return back;
            else
                return back->next;
        }

        ListNode *pair = helper(front->next, back, ans, isEven);
        ans = ans && front->val == pair->val;
        return pair->next;
    }
    bool isPalindrome(ListNode *head)
    {
        if (head->next == nullptr)
            return true;
        ListNode *fast = head;
        ListNode *slow = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        bool isEven = true;
        if (fast != nullptr)
            isEven = false;
        // slow is ceil(median)

        bool ans = true;
        helper(head, slow, ans, isEven);
        return ans;
    }
};

/**
 * Using a LEGNTH
 */
class Solution
{
public:
    ListNode *helper(ListNode *front, int length, bool &ans)
    {
        if (length == 2)
        {
            ans = ans && front->val == front->next->val;
            return front->next->next;
        }
        else if (length == 1)
        {
            return front->next;
        }

        ListNode *back = helper(front->next, length - 2, ans);
        ans = ans && front->val == back->val;
        return back->next;
    }
    bool isPalindrome(ListNode *head)
    {
        if (head->next == nullptr)
            return true;
        ListNode *curr = head;
        int length = 0;
        while (curr != nullptr)
        {
            curr = curr->next;
            ++length;
        }

        bool ans = true;
        helper(head, length, ans);
        return ans;
    }
};