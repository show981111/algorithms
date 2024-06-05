class Solution
{
public:
    /*
    Push right once at a time.
    If we reach k number of different integers, shrink left and count subarrs until it becomes == k.
    We should keep the windowto the minimum size that contains exactly "k" numbers, so that
    we can tell if we can concat the next integer to make a new good subarray (to check if that number
    is already in the window to make a good array)
    Move right, if that number is already included num, we concat this number to prev subarr!

    [1,2,|1|,]
    */
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        int goodArrayCnt = 0;
        int prevCnt = 0;
        unordered_map<int, int> freq;
        int left = 0, right = 0;

        while (right < nums.size())
        {
            int curCnt = 0;
            int n = nums[right++];
            if (freq.count(n) > 0 && prevCnt > 0)
            {
                // including this number doesn't affect previous good subarray that ends at i-1.
                // Due to this, we need to maintain the window to include exactly k integers(but minimum size)
                curCnt += (prevCnt - 1);
            }
            freq[n]++;

            while (freq.size() >= k)
            {
                if (freq.size() == k)
                {
                    curCnt++;
                }
                int l = nums[left];
                if (freq.size() == k && freq[l] == 1)
                {
                    break; // minimum window size with freq.size() ==k
                }
                else
                {
                    freq[l]--;
                    if (freq[l] == 0)
                        freq.erase(l);
                }
                left++;
            }
            goodArrayCnt += curCnt;
            prevCnt = curCnt;
        }
        return goodArrayCnt;
    }
};

class Solution
{
public:
    int atMostK(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        int start = 0, end = 0;
        int n = nums.size();
        int ways = 0;

        while (start < n && end < n)
        {
            mp[nums[end]]++;

            if (mp.size() > k)
            {
                while (start < n && start <= end && mp.size() > k)
                {
                    mp[nums[start]]--;
                    if (mp[nums[start]] == 0)
                        mp.erase(nums[start]);
                    start++;
                }
            }
            // number of subarrays that <ends with "end"> and contains at most K distinct integers
            // ex) [1,2] and end = 2, k = 2 -> [1,2] and [2] so 2
            // why end - start + 1?
            // [n_1, n_2, ... , n_k] -> then
            // [n_1,n_2, ... , n_k](size k) , [n_2, ... , n_k](size k -1), [n_3, ... , n_k](size k-2) ...
            ways += end - start + 1;
            end++;
        }
        return ways;
    }
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {

        //     / 1 /2 /1 2 3
        // T(N) = if mp.size() is the same T(N-1) + #subArr ending with N
        // ways: 0 1  3 5
        // memo: 0 1         2                3
        //       [1,2] [2,1],[1,2,1]  [1,2,1,2], [2,1,2], [1,2]

        // How to pull back the start?
        // after we push start to count all subarray ending with "end",
        // we need to pull this back to count all subarray ending with "end+1"

        // Key of this problem. Exact K == MostK - Most_K-1

        return atMostK(nums, k) - atMostK(nums, k - 1);
    }
};

/**
 * @brief One Pass Using prefix!
 * If current number was already in before -> we can add
 * current number to previous one to make a new subarray!
 * -> ADD previous count again!
 *
 */
class Solution
{
public:
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        int start = 0, end = 0;
        int prevWays = 0;
        int ways = 0;
        // mp[end]++
        // 1 2 1 2 3
        // if mp.size() == k -> +1 if we just got k. If end is alr there, add += prevWays
        //                   + Shrink Window, count all subwindows!
        //               < k -> just keep expanding END
        //               > k -> shrink window
        while (end < nums.size())
        {
            int tempWays = ways;
            mp[nums[end]]++;
            if (mp.size() == k && mp[nums[end]] > 1)
            { // we added something that was alr there
                ways += prevWays;
            }
            else if (mp.size() == k && mp[nums[end]] == 1)
            {
                ways++; // just made K size array!
            }

            while (mp.size() >= k)
            {
                if (mp[nums[start]] == 1 && mp.size() == k)
                {
                    break; // should keep the window with K diff integers.
                }          // becuz we cannot know if next element is redundant or not
                           // ex) [1,2],1 -> we deleted first 1, 1,[2],3 -> 1,[2,1]
                           // oh should I add prevWays or not? cuz mp[1] = 1. Doesn't know
                           // previous sliding window was [1,2]
                ways++;
                mp[nums[start]]--;
                if (mp[nums[start]] == 0)
                {
                    mp.erase(nums[start]);
                }
                start++;
            }
            // if(ways == tempWays && mp.size() == k ) ways++;
            prevWays = ways - tempWays;
            end++;
        }

        return ways;
    }
};