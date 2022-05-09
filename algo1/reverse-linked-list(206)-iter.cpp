/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *reverseList(ListNode *head) // WE can USE STACK
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *cur = head;
        ListNode *post = cur->next;
        ListNode *temp;
        while (post != nullptr)
        {
            temp = post;       //
            post = post->next; // forward the iteration
            temp->next = cur;  // reverse two node [cur -> temp -> post] => [cur <- temp -> post]
            // cout << temp->val << " ~ " << cur->val << endl;
            cur = temp; // forward cur to follow post [cur -> post]
        }
        head->next = nullptr;
        return cur;
    }
};