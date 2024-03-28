/**
 * Continuous target sum(subarray sum) => Prefix!
 *
 * Sum[i:j] = Prefix[j] - Prefix[i-1]
 *
 * Using dummyHead for list is convenient to deal with the case where we remove the head!
 */

class Solution
{
public:
    ListNode *removeZeroSum(ListNode *head)
    {
        unordered_map<int, ListNode *> prefix;
        int prefixSum = 0;
        ListNode *tempHead = new ListNode;
        tempHead->next = head;
        ListNode *cur = tempHead;
        while (cur)
        {
            prefixSum += cur->val;
            if (prefix.count(prefixSum) > 0)
            {
                // want to delete (prefix[prefixSum]->next ~ cur)
                ListNode *newCur = cur->next;

                ListNode *toDelete = prefix[prefixSum]->next;
                int sumToDelete = prefixSum;
                prefix[prefixSum]->next = newCur;

                while (toDelete && toDelete != newCur)
                {
                    sumToDelete += toDelete->val;
                    prefixSum -= toDelete->val;
                    if (toDelete != cur)
                    {
                        prefix.erase(sumToDelete);
                    }
                    ListNode *temp = toDelete;
                    toDelete = toDelete->next;
                }
                cur = newCur;
            }
            else
            {
                prefix[prefixSum] = cur;
                cur = cur->next;
            }
        }
        ListNode *ret = tempHead->next;
        delete tempHead;
        return ret;
    }
    ListNode *removeZeroSumSublists(ListNode *head)
    {
        return removeZeroSum(head);
    }
};