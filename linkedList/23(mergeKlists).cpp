#include <iostream>
#include <vector>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.size() == 0)
            return nullptr;

        ListNode *cur = new ListNode();
        ListNode *dummyHead = cur;

        while (1)
        {
            ListNode *min = lists[0];
            int minIndex = 0;
            bool isAllNull = true;
            for (int i = 0; i < lists.size(); i++)
            {
                if (lists[i] == nullptr)
                    continue;
                isAllNull = false;
                if (min == nullptr)
                {
                    min = lists[i];
                    minIndex = i;
                    continue;
                }
                if (min->val > lists[i]->val)
                {
                    min = lists[i];
                    minIndex = i;
                }
            }
            if (isAllNull)
                break;
            cur->next = min;
            cur = cur->next;
            lists[minIndex] = lists[minIndex]->next;
        }
        ListNode *realHead = dummyHead->next;
        delete dummyHead;
        return realHead;
    }
};