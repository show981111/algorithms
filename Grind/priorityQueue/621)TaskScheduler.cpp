/**
 * @brief If we have a priority to do something... => priority queue!!
 *
 * When we have to delay something.. => put that item to temporary storage,
 * then after the required time has passed, we can just retrieve that item from the storage.
 *
 * In this problem, I should exclude the task I used for 'n' amount of time.
 * Thus, I put the task to Queue and push it to the PQ later when 'n' time is passed.
 *
 * Priority => number of tasks.
 * We should process the most frequent task(s) first at a given time.
 */

class Solution
{
public:
    struct Task
    {
        char task;
        int num;
        int execAt;
        Task(char t, int n, int e) : task(t), num(n), execAt(e) {}
    };

    class Comp
    {
    public:
        bool operator()(const Task &a, const Task &b)
        {
            if (a.num < b.num)
                return true;
            else
                return false;
        }
    };
    int leastInterval(vector<char> &tasks, int n)
    {
        unordered_map<char, int> mp;
        for (char c : tasks)
        {
            mp[c]++;
        }
        priority_queue<Task, vector<Task>, Comp> pq;
        for (auto iter : mp)
        {
            pq.push(Task(iter.first, iter.second, -1));
        }

        queue<Task> temp;
        int time = 0;

        while (!pq.empty() || !temp.empty())
        {
            if (!pq.empty())
            {
                Task t = pq.top();
                t.num--;
                t.execAt = time;
                pq.pop();
                if (t.num > 0) // still need to process this task
                {
                    temp.push(t);
                }
            }
            if (!temp.empty() && time - temp.front().execAt >= n)
            // we can process this element if n amount of time has passed
            {
                pq.push(temp.front()); // re-push it with different priority(num is decreased)
                temp.pop();
            }
            time++;
        }
        return time;
    }
};

// Same Idea but using a cycle
// We call the 'n' amount of time as a cycle, first process the cycle, and later
// process the residual tasks.
// Within cycle we can just re-arrange tasks
class Solution
{
public:
    struct Task
    {
        char task;
        int num;
        int execAt;
        Task(char t, int n, int e) : task(t), num(n), execAt(e) {}
    };

    class Comp
    {
    public:
        bool operator()(const Task &a, const Task &b)
        {
            if (a.num < b.num)
                return true;
            else
                return false;
        }
    };
    int leastInterval(vector<char> &tasks, int n)
    {
        unordered_map<char, int> mp;
        for (char c : tasks)
        {
            mp[c]++;
        }
        priority_queue<Task, vector<Task>, Comp> pq;
        for (auto iter : mp)
        {
            pq.push(Task(iter.first, iter.second, -1));
        }

        queue<Task> temp;
        int time = 0;
        int cycle = n + 1;
        while (!pq.empty())
        {
            for (int i = 0; i < cycle; i++)
            {
                if (!pq.empty())
                {
                    if (pq.top().num > 1)
                        temp.push(pq.top());
                    pq.pop();
                }
                else
                {
                    if (temp.empty())
                        break;
                }
                time++;
            }
            while (!temp.empty())
            {
                if (--temp.front().num > 0)
                {
                    pq.push(temp.front());
                }
                temp.pop();
            }
        }

        return time;
    }
};

// O(N), O(1) space,
// Using math to find how many empty slots should be allocated
// Key idea is how many idles(do nothing) we need!
// https://leetcode.com/problems/task-scheduler/discuss/104500/Java-O(n)-time-O(1)-space-1-pass-no-sorting-solution-with-detailed-explanation

class Solution
{
public:
    int leastInterval(vector<char> &tasks, int n)
    {
        int freq[26] = {
            0,
        };
        int maxFreq = 0;
        int maxCount = 0;
        for (auto t : tasks)
        {
            freq[t - 'A']++;
            if (freq[t - 'A'] == maxFreq)
                maxCount++;
            else if (freq[t - 'A'] > maxFreq)
            {
                maxFreq = freq[t - 'A'];
                maxCount = 1;
            }
        }

        int chunkCount = (maxFreq - 1);
        int emptySlots = n * chunkCount - (maxCount - 1) * chunkCount;
        int residueTasks = tasks.size() - maxFreq * maxCount;
        int idles = max(0, emptySlots - residueTasks);

        return tasks.size() + idles;
    }
};