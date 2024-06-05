class Solution
{
public:
    /*
    1. Push right one at a time.
    - If we encounter a number < minK and > maxK, then we cannot
    make any good subarray by including this num. So we should restart from after that num!
    - If the number is minK <= N <= maxK, concat this to make another subarrs (add prevCnt)

    2. Shrink until the subarray is not good.

    Using an Ordered Map to track min and max.
    However, is it necessary? do we need to know next min when we pop current min? NO!
    We only care about all numbers are in minK ~ maxK and also we have both minK and maxK.
    So if we don't have minK and maxK, we are done. => Just store the location of minK and maxK!
    */
    long long countSubarrays(vector<int> &nums, int minK, int maxK)
    {
        long long cnt = 0;
        int prevCnt = 0;
        int left = 0, right = 0;
        map<int, int> mp;

        while (right < nums.size())
        {
            int curCnt = 0;
            int n = nums[right++];
            mp[n]++;
            if (n >= minK && n <= maxK)
            {
                curCnt += prevCnt;
            }
            else if (n < minK || n > maxK)
            {
                // now cannot make any good subarray including this elem.
                mp.clear();
                prevCnt = 0;
                left = right;
                continue;
            }

            while (mp.begin()->first == minK && mp.rbegin()->first == maxK)
            {
                // good array!
                curCnt++;
                int evict = nums[left++];
                if (mp[evict] == 1)
                {
                    mp.erase(evict);
                }
                else
                {
                    mp[evict]--;
                }
            }
            cnt += curCnt;
            prevCnt = curCnt;
        }
        return cnt;
    }
};

/**
 * Only store the idx of min and max. No need to manage heap.
 *
 * If we only need to know the idx of min and max... we can count # of subarrays using this!
 * Let bad_idx be a number that are out of range ( <minK, > maxK)
[bad_idx, ..., minK_idx, ..., maxK_idx,... i]
number of good subarrays ending at I is,
** minK - bad_idx ** since we can make
[bad_idx+1 ~ minK_idx ~ maxK_idx, i]
[bad_idx+2 ~ minK_idx ~ maxK_idx, i]
[bad_idx+(minK_idx - bad_idx) ~ minK_idx ~ maxK_idx, i]

Using this, we can do better!
 */

void clearQueue(queue<int> &q)
{
    while (!q.empty())
        q.pop();
}
long long countSubarrays(vector<int> &nums, int minK, int maxK)
{
    long long cnt = 0;
    int prevCnt = 0;
    int left = 0, right = 0;
    queue<int> minIndices;
    queue<int> maxIndices;

    while (right < nums.size())
    {
        int curCnt = 0;
        int n = nums[right];
        if (n == minK)
            minIndices.push(right);
        if (n == maxK)
            maxIndices.push(right);
        right++;
        if (n >= minK && n <= maxK)
        {
            curCnt += prevCnt;
        }
        else if (n < minK || n > maxK)
        {
            // now cannot make any good subarray including this elem.
            prevCnt = 0;
            clearQueue(minIndices);
            clearQueue(maxIndices);
            left = right;
            continue;
        }

        while (minIndices.size() > 0 && maxIndices.size() > 0)
        {
            // good array!
            curCnt++;
            if (minIndices.front() == left)
            {
                minIndices.pop();
            }
            if (maxIndices.front() == left)
            {
                maxIndices.pop();
            }
            left++;
        }
        cnt += curCnt;
        prevCnt = curCnt;
    }
    return cnt;
}

/**
 * Final simplest version.
 */
long long countSubarrays(vector<int> &nums, int minK, int maxK)
{
    long long cnt = 0;
    int prevCnt = 0;
    int N = nums.size();
    int last_min_idx = -1, last_max_idx = -1;
    int last_bad_idx = -1;

    for (int i = 0; i < N; i++)
    {
        if (nums[i] == minK)
        {
            last_min_idx = i;
        }
        if (nums[i] == maxK)
        {
            last_max_idx = i;
        }
        if (nums[i] < minK || nums[i] > maxK)
        {
            last_bad_idx = i;
        }
        int goodArrStarts = min(last_min_idx, last_max_idx);
        cnt += max(0, goodArrStarts - last_bad_idx);
    }
    return cnt;
}