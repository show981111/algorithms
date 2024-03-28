/**
 * @brief If we have a priority to do something... => priority queue!!
 *
 * When we have to delay something.. => put that item to temporary storage,
 * then after the required time has passed, we can just retrieve that item from the storage.
 *
 * In this problem, I should exclude the task I used for 'n' amount of time.
 * Thus, I put the task to Queue and push it to the PQ later when 'n' time is passed.
 *
 * KEY OF THIS PROBLEM IS,
 * We should assign the tasks that has the biggest frequency first.
 * This means, we should keep track of how many tasks we have left per each task type,
 * and assign them in order.
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
    using Pair = pair<int, int>; // id, cnt
    int leastInterval(vector<char> &tasks, int n)
    {
        vector<int> taskCnt(28, 0);
        for (char &c : tasks)
        {
            taskCnt[c - 'A']++;
        }
        auto comp = [](const Pair &a, const Pair &b)
        {
            return a.second < b.second;
        };
        priority_queue<Pair, vector<Pair>, decltype(comp)> pq(comp);
        queue<Pair> rest;

        for (int i = 0; i < 28; i++)
        {
            if (taskCnt[i] > 0)
            {
                pq.push({i, taskCnt[i]});
            }
        }
        int t = 0;
        while (!pq.empty())
        {
            for (int i = 0; i < n + 1; i++)
            { // max Length of each cycle.
                if (pq.size() > 0)
                {
                    t++;
                    Pair t = pq.top();
                    pq.pop();
                    t.second--;
                    // assign to this cycle
                    if (t.second > 0)
                    {
                        // take rest
                        rest.push(t);
                    }
                }
                else
                {
                    // cannot assign any tasks..
                    if (rest.empty())
                    {
                        break; // we assigned all tasks, break.
                    }          // else just idle..
                    t++;
                }
            }
            while (rest.size() > 0)
            {
                pq.push(rest.front());
                rest.pop();
                // had enough rest, push back to pq so that we can assign during cycle.
            }
        }
        return t;
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

/*
How to pack as many different task as possible in one cycle.
Greedy approach.
*/
class Solution
{
public:
    using Pair = pair<int, int>; // id, cnt
    int leastInterval(vector<char> &tasks, int n)
    {
        vector<int> taskCnt(28, 0);
        for (char &c : tasks)
        {
            taskCnt[c - 'A']++;
        }
        vector<Pair> sortedTasks;
        for (int i = 0; i < 28; i++)
        {
            if (taskCnt[i] > 0)
            {
                sortedTasks.push_back({i, taskCnt[i]});
            }
        }
        sort(sortedTasks.begin(), sortedTasks.end(), [](const Pair &a, const Pair &b)
             { return a.second > b.second; });
        int maxFreq = sortedTasks[0].second;
        int lastChunkSize = 1;
        for (int i = 1; i < sortedTasks.size(); i++)
        {
            if (sortedTasks[i].second == maxFreq)
            {
                lastChunkSize++; // Since max one unqiue task can go into each chunk
                // If we have maxFreq amount of tasks, it will have to use the last chunk
            }
            else
                break;
        }
        int residual = tasks.size() - maxFreq * lastChunkSize;
        if (residual >= (n + 1 - lastChunkSize) * (maxFreq - 1))
        {
            // After assigninig maxFreq tasks, if the leftover cannot fit into n+1 diemnsion
            return tasks.size();
        }
        else
        {
            // Otherwise, each chunk should be n+1 length.
            return (n + 1) * (maxFreq - 1) + lastChunkSize;
        }
        return 0;
    }
};
/*
Why hard?
If we are going to exceed the capacity of each chunk, distiribute the task evenly.
Otherwise, pack as many before the last chunk!
We gotta put as little as possible to the last chunk

Alignment is important
A B C E <FULL>
A B C E <FULL>
A B D <C>
A B D
A <C> D
We can move C, but can't move D! Optimal would be
A B C E
A B C D
A B C D
A B E D
A
So we cannot just assign tasks from 0 ~ maxFreq as we go.

A B C D E
A B C D
A B C
*/