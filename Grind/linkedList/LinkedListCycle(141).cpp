/**
 * @brief Cycle Detection Algorithm using 2pointers!
 * algo2 HappyNumbers
 *
 * Cycle Detection in Graph
 * - Directed : DFS or BFS
 * - Undirected : union find
 *
 * Using do-while loop
 * do-while loop execute the "do" first only for the first cycle.
 * So while and do-while is the same when we know the while loop is running
 * at least one time.
 */

class Solution
{
public:
    ListNode *next(ListNode *cur)
    {
        if (cur == nullptr)
            return nullptr;
        else
            return cur->next;
    }
    bool hasCycle(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;
        do
        {
            fast = next(next(fast));
            slow = next(slow);
        } while (fast != slow);

        return fast != nullptr;
    }
};