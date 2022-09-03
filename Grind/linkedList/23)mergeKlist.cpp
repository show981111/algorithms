/**
 * @brief First Naive approach
 * Time Complexity: O(K*KN)
 *  We select the head of each linked list and get min (O(K) since there are K lists)
 *  We repeat this process until we process all elements(K*N)
 *  So, O(K*KN)
 */

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *dummyHead = new ListNode(1);
        ListNode *cur = dummyHead;
        int N = lists.size();
        int i = 0;
        while (1)
        {
            int minIndex = -1;
            int minVal = 10001;
            for (int l = 0; l < N; l++)
            {
                if (lists[l] != nullptr && lists[l]->val < minVal)
                {
                    minIndex = l;
                    minVal = lists[l]->val;
                }
            }
            if (minIndex != -1)
            {
                cur->next = lists[minIndex];
                cur = cur->next;
                lists[minIndex] = lists[minIndex]->next;
            }
            else
            {
                break;
            }
        }
        ListNode *realHead = dummyHead->next;
        delete dummyHead;
        return realHead;
    }
};

/**
 * @brief Second PQ
 * Time comp : O(nk*logk)
 * the size of pq is kept to K,
 * then pop element and push element nk times because there are nk nodes.
 */

class Solution
{
public:
    // using a pq, O(nk*logk)
    class Comp
    {
    public:
        // if we use const ListNode* &a, &b, then we get compiler error!
        bool operator()(const ListNode *a, const ListNode *b)
        {
            return a->val > b->val;
        }
    };
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *dummyHead = new ListNode(1);
        ListNode *cur = dummyHead;
        int N = lists.size();
        int i = 0;

        priority_queue<ListNode *, vector<ListNode *>, Comp> pq;
        for (int l = 0; l < N; l++)
        {
            if (lists[l] != nullptr)
            {
                pq.push(lists[l]);
            }
        }
        while (!pq.empty())
        {
            ListNode *f = pq.top();
            cur->next = f;
            pq.pop();
            cur = cur->next;
            if (f->next != nullptr)
                pq.push(f->next);
        }

        ListNode *realHead = dummyHead->next;
        delete dummyHead;
        return realHead;
    }
};

/**
 * @brief Third attempt -> divide and conquer
 * merge two lists at a time.
 * merge two lists => O(2*(length of each list))
 * (1) O(2*N)*(K/2) = NK, first level, merge N length lists
 * (2) O(2*2N)*(K/4) = NK, second level, merge 2N length lists and there are total K/2 lists,
 * so merge is K/4 times.
 * (i) O(2^i*N)*(K/(2^i)) = NK, i_th level, merge iN length lists...
 *
 * Sum up, 2^i = K, i = logK so,
 * logK * NK = O(NK*logK)
 */
class Solution
{
public:
    ListNode *merge(ListNode *a, ListNode *b)
    {
        if (a == nullptr)
            return b;
        if (b == nullptr)
            return a;
        if (a->val <= b->val)
        {
            a->next = merge(a->next, b);
            return a;
        }
        else
        {
            b->next = merge(a, b->next);
            return b;
        }
    }
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty())
            return nullptr; // if lists is empty, it returns lists[0], so out of index
        int len = lists.size();
        while (len > 1)
        {
            for (int i = 0; i < (len / 2); i++)
            {
                lists[i] = merge(lists[i], lists[len - i - 1]);
                // merge i and len-i-1 and put it into i. so, elements from 0 ~ len/ 2 are
                // updated merged lists
            }
            len = (len + 1) / 2; // add 1 to len because it should include
                                 // the element in the middle in the case of when len is odd
        }
        return lists[0];
    }
};