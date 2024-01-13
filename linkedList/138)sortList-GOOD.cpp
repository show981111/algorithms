/**
 * Sorting a linked list => Can be done in O(nlogn) if we use merge sort.
 *
 * Other sorting algos will require random access(accessing using an index) which is impossible in linked list.
 *
 * Key point.
 * Moving nodes VS Moving values(keep nodes but overwrites node->val)
 *
 * which one is easier?
 * Moving values will require us to store values in a separate data structure when merging.
 *
 * EX) 4 5 6 + 1 2 3
 * if we want to keep the nodes, then we gotta overwrite 1,2,3 to 4,5,6 nodes.
 * This requires us to store 4,5,6 to somewhere so that we can use this value when we overwrite 1,2,3 nodes. => O(N) space complexity.
 *
 * If we moving around nodes, we can merge two sorted lists in O(1) space. Just reorder nodes.
 * 4 5 6 + 1 2 3
 * 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr (just reorder nodes)
 *
 *
 */

class Solution
{
public:
    const int MAXVAL = 100003;
    ListNode *getMid(ListNode *start, ListNode *end)
    {
        ListNode *fast = start, *slow = start;

        while (fast && fast->next && fast != end && fast->next != end)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode *merge(ListNode *fir, ListNode *sec)
    {
        ListNode *dummyHead = new ListNode; // temporary head
        ListNode *cur = dummyHead;
        // merging is done by moving nodes around. It is easier then just moving around values
        // because we have to overwrite nodes if we are moving values and it will require us
        // to save those values in somewhere
        while (fir != nullptr || sec != nullptr)
        {
            if (fir == nullptr)
            {
                cur->next = sec;
                sec = sec->next;
            }
            else if (sec == nullptr)
            {
                cur->next = fir;
                fir = fir->next;
            }
            else
            {
                if (fir->val < sec->val)
                {
                    cur->next = fir;
                    fir = fir->next;
                }
                else
                {
                    cur->next = sec;
                    sec = sec->next;
                }
            }
            cur = cur->next;
        }
        cur->next = nullptr; // make the end nullptr so that it does not refer any
                             // old nodes from the list
        ListNode *head = dummyHead->next;
        delete dummyHead;
        return head;
    }
    ListNode *sort(ListNode *start, ListNode *end)
    {
        if (start == nullptr || start->next == end)
        {
            if (start)
                start->next = nullptr; // separate each node
            return start;
        } // exclusive end. For linked list, exclusive end is much easier due to nullptr at the end. Also no need to track the end node

        // get median from this range
        ListNode *m = getMid(start, end); // O(N)

        ListNode *f = sort(start, m); // get head of first half
        ListNode *s = sort(m, end);   // get head of second half
        ListNode *r = merge(f, s);    // merge them
        return r;
    }
    ListNode *sortList(ListNode *head)
    {
        return sort(head, nullptr);
    }
};

/**
 *
 * Initial version with Range
 *
 * Range structure is not needed because end is always a nullptr.
 * We only need end when we get a middle node. Other then that, we can just end a new sorted list with nullptr
 * so that nodes don't refer to wrong old nodes at the end.
 */

class Solution
{
public:
    const int MAXVAL = 100003;
    typedef pair<ListNode *, ListNode *> Range;
    ListNode *getMid(ListNode *start, ListNode *end)
    {
        ListNode *fast = start, *slow = start;

        while (fast && fast->next && fast != end && fast->next != end)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    Range merge(ListNode *fir, ListNode *firEnd, ListNode *sec, ListNode *secEnd)
    {
        ListNode *dummyHead = new ListNode;
        ListNode *cur = dummyHead;
        while (fir != firEnd || sec != secEnd)
        {
            if (fir == firEnd)
            {
                cur->next = sec;
                sec = sec->next;
            }
            else if (sec == secEnd)
            {
                cur->next = fir;
                fir = fir->next;
            }
            else
            {
                if (fir->val < sec->val)
                {
                    cur->next = fir;
                    fir = fir->next;
                }
                else
                {
                    cur->next = sec;
                    sec = sec->next;
                }
            }
            cur = cur->next;
        }
        cout << endl;
        cur->next = nullptr;
        Range r{dummyHead->next, cur->next};
        delete dummyHead;
        return r;
    }
    Range sort(ListNode *start, ListNode *end)
    {
        if (start == nullptr || start->next == end)
            return {start, end};          // exclusive end
        ListNode *m = getMid(start, end); // O(N)
        Range f = sort(start, m);
        Range s = sort(m, end);

        Range r = merge(f.first, f.second, s.first, s.second);
        return r;
    }
    ListNode *sortList(ListNode *head)
    {
        Range r = sort(head, nullptr);
        return r.first;
    }
};
