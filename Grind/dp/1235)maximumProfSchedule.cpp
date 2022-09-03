/**
 * @brief Maximum profit according to each time line
 * we have a choice of include/exclude current element.
 * => Knapsack
 * => DP!!
 *
 * T(N) = max(T(N-k) + profit[k], T(N-1))
 *            Include kth elem  , exclude kth elem
 */

/**
 * @brief First attempt
 * Memory limit
 * We make an array according to the max end time.
 * and record the max according to that end time.
 *
 * the length of memo is max(endTimes)
 * if we have [3, 4, 1000000] of endTimes,
 * then the length becomes 1000000, => memory limit!
 */

class Solution
{
public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {
        int maxEndTime = -1;
        unordered_map<int, vector<int>> endTimeToIndex;

        for (int i = 0; i < endTime.size(); i++)
        {
            maxEndTime = max(endTime[i], maxEndTime);
            endTimeToIndex[endTime[i]].push_back(i);
        }
        vector<int> memo(maxEndTime + 1, 0);

        for (int i = 1; i <= maxEndTime; i++)
        {
            int prof = 0;
            if (endTimeToIndex.find(i) != endTimeToIndex.end())
            {
                vector<int> jobsThatEndsNow = endTimeToIndex[i];
                for (int index : jobsThatEndsNow)
                {
                    prof = max(prof, memo[startTime[index]] + profit[index]);
                }
            }
            memo[i] = max(memo[i - 1], prof);
        }
        return memo.back();
    }
};

/**
 * @brief Second Attempt
 * Create a map to conver from endTime to index,
 * and start time to index
 * Memo[i] => the maximum profit from [0 ~ timeline[i]]
 * time : O(nlogn) due to sort
 */

class Solution
{
public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {
        int maxEndTime = -1;
        unordered_map<int, vector<int>> endTimeToIndex;
        vector<int> timeline(startTime.begin(), startTime.end());
        timeline.insert(timeline.end(), endTime.begin(), endTime.end());
        sort(timeline.begin(), timeline.end());
        timeline.erase(unique(timeline.begin(), timeline.end()), timeline.end());

        vector<int> memo(timeline.size());
        for (int i = 0; i < endTime.size(); i++)
        {
            endTimeToIndex[endTime[i]].push_back(i);
        }
        unordered_map<int, int> timeToMemo;
        for (int i = 0; i < timeline.size(); i++)
        {
            timeToMemo[timeline[i]] = i;
        }

        for (int i = 1; i < timeline.size(); i++)
        {
            int time = timeline[i];
            int prof = 0;
            if (endTimeToIndex.find(time) != endTimeToIndex.end())
            {
                vector<int> jobsThatEndsNow = endTimeToIndex[time];
                for (int index : jobsThatEndsNow)
                {
                    int startTimetoMemoIndex = timeToMemo[startTime[index]];
                    prof = max(prof, memo[startTimetoMemoIndex] + profit[index]);
                }
            }
            memo[i] = max(memo[i - 1], prof);
        }
        return memo.back();
    }
};

/**
 * @brief Third Attempt
 * More concise.
 * Instead of creating a map, we use binary search to find
 * the last element before current job starts.
 *
 * memo[i] = the maximum profit when i_th job ends.
 *
 * Lower_bound? or Upper_bound
 *
 * We should get the last element such that currentJob.startTime >= job.endTime
 * So we should use upper_bound and decrement the index!
 * Upper_bound gets the first element such that val < elem
 * lower_bound gets the first element such that val <= elem
 *
 */

class Solution
{
public:
    struct Job
    {
        int startTime;
        int endTime;
        int profit;
    };
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {
        vector<Job> jobs;
        for (int i = 0; i < startTime.size(); i++)
        {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
             { return a.endTime < b.endTime; });
        int N = jobs.size();
        vector<int> memo(N);
        // for endTime of ith job in jobs, max profit
        memo[0] = jobs[0].profit;

        for (int i = 1; i < N; i++)
        {
            auto beforeCurJobIt = upper_bound(jobs.begin(), jobs.begin() + i, jobs[i].startTime, [](const int &val, const Job &elem)
                                              { return val < elem.endTime; });
            int beforeCurJobIndex = beforeCurJobIt - jobs.begin();
            int prevProfit = 0;
            if (beforeCurJobIndex >= 0 && beforeCurJobIndex < N)
            {
                if (jobs[beforeCurJobIndex].endTime > jobs[i].startTime)
                    beforeCurJobIndex--;
                if (beforeCurJobIndex >= 0)
                {
                    prevProfit = memo[beforeCurJobIndex];
                }
            }
            memo[i] = max(memo[i - 1], jobs[i].profit + prevProfit);
        }
        return memo.back();
    }
};