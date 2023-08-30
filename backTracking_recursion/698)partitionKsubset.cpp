/**
 * @brief Pass TLE with memo
 * Why we only need to mark 0,1?
 * we are not interested in how those elems make the subset.
 * We only need to know if we used this one to make a subset or not.
 *
 * Why we can memo this result?
 * !!!!!! We creates different subsets with same sum using same elems. We know that does not work!!
 * ex) [1,2,3,4,5,6,7]
 * 00X0X1X VS 01X1X0X
 * [1,2,4], [6] VS [1,6], [2,4]
 * we know [1,2,4] = 7 & [6] = 6 does not work.
 * and [1,6] = 7 & [2,4] = 6 should not work. because it uses the same elements
 * and the sum of each subset corresponds. If the later case works by [1,6], [2,4,X], [Y,Z], then
 * THe first case shouldve worked by [1,2,4], [6,X], [Y,Z]
 * Thus, we can cache this!
 */
class Solution
{
public:
    // what's redundant? trying subset multiple times
    // ex) {1,2,3} {4,5} doesnt work! but will try {2,1,3} again!
    // why hard to detect? Subset could be fine, comb of subset might wrong and dont know
    // which subset is wrong...

    // permutation -> combination : Play with curIndex. Preventing selecting from 0-index
    // its like giving an order when selecting elems

    // still, {1,2,3} = 1, {4,5} = 2 Not works, but will try {4,5} = 1, {1,2,3} = 2
    // cannot prevent this... cuz we have to until the end to figure out if it works or not
    // Now the problem is redundant elems. {1,1,2,2,3,3}
    // will try {1,2,3}, {1(B),2,3} again and again
    bool canPartition(vector<int> &nums, int target, int k, int curSum, int curSubsetIndex, vector<int> &subset, int curIndex, unordered_set<string> &memo)
    {
        if (curSubsetIndex == k - 1)
            return true;
        if (curIndex >= nums.size())
            return false;

        if (memo.find(makeString(subset)) != memo.end())
        {
            // cout << "redundant!\n";
            return false;
        }

        bool res = false;
        for (int i = curIndex; i < nums.size(); i++)
        {
            // if(i>curIndex && nums[i] == nums[i-1]) continue;
            // if(curSum + nums[i] > target) break;
            if (subset[i] == 0 && curSum + nums[i] <= target)
            {
                subset[i] = 1;
                if (curSum + nums[i] == target)
                {
                    res = canPartition(nums, target, k, 0, curSubsetIndex + 1, subset, 0, memo);
                }
                else
                {
                    res = canPartition(nums, target, k, curSum + nums[i], curSubsetIndex, subset, i + 1, memo);
                }
                if (res)
                    return res;
                subset[i] = 0;
            }
        }
        memo.insert(makeString(subset));
        return false;
    }

    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int sum = 0;
        for (int num : nums)
            sum += num;
        if (sum % k != 0)
            return false;
        int target = sum / k;
        vector<int> subset(nums.size(), 0);
        unordered_set<string> st;
        return canPartition(nums, target, k, 0, 0, subset, 0, st);
    }

    string makeString(vector<int> &v)
    {
        string x = "";
        for (int num : v)
        {
            x += to_string(num);
        }
        return x;
    }
};

/**
 * @brief First thought
 * Subset with sum K, knapsack?
 * But we cannot do knapsack because we do not know which elem we used or not used
 * => Backtracking...
 *
 * Why it is hard?
 *  A) even though we got subsets which are sum up to K, we should see if they are non-overlapping
 *  B) there are unique elems in array... how to pick as many they exist?
 *  C) let's say we use backtracking and reached targetSum, what should we do next?
 *      what should we do with curIndex?
 *      => we should set curIndex = 0; to select from the beginning.
 *      curIndex is used to skip redundant elems
 *      So, I used the map, and start iterating from the beginning ... (using a map will make a permutation!)
 *      -> this still picking up redundant elems! because it starts over from the beginning,
 *      so we might select the same elements but in a different order.
 *      -> so we need to figure out how to use curIndex, so we came up with vector<pair<int,int>>
 *      ex) <1: 2> <2 : 1> <3:2>
 *          -> 1, 1, 2, 3, 3 Also, 1, 2, 1, 3, 3 are possible if use map
 *          ->
 * https://leetcode.com/problems/partition-to-k-equal-sum-subsets/solutions/335668/dp-with-bit-masking-solution-best-for-interviews/
 */

class Solution
{
public:
    bool backTrack(vector<pair<int, int>> &freq, int curIndex, int curSum, int &accumSum, int setCount)
    {
        if (setCount == targetK && accumSum == totalSum)
            return true;

        if (curSum == target)
        {
            setCount++;
            // cout << target <<" " << setCount <<" " << accumSum << endl;
            if ((totalSum - accumSum) != (targetK - setCount) * target)
                return false;
            if (backTrack(freq, 0, 0, accumSum, setCount))
            { // start from 0
                return true;
            }
        }
        if (curIndex == freq.size())
        {
            if (setCount == targetK)
                return true;
        }

        bool res = false;
        for (int i = curIndex; i < freq.size(); i++)
        {
            if (freq[i].second > 0)
            {
                freq[i].second--;
                accumSum += freq[i].first;
                res = backTrack(freq, i, curSum + freq[i].first, accumSum, setCount);
                accumSum -= freq[i].first;
                freq[i].second++;
                if (res)
                    return res;
            }
        }
        return res;
    }
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int N = nums.size();
        targetK = k;
        unordered_map<int, int> mp;
        vector<pair<int, int>> freq;
        for (auto n : nums)
        {
            mp[n]++;
            totalSum += n;
        }
        if (totalSum % k != 0)
            return false;
        for (auto &iter : mp)
        {
            freq.push_back(iter);
        }
        target = totalSum / k;
        int accum = 0;
        return backTrack(freq, 0, 0, accum, 0);
    }

private:
    int totalSum = 0;
    int target = 0;
    int targetK = 0;
};
/**
[1,1,1,2,3]
4
[1,1]
1
*/

class Solution
{
public:
    // what's redundant? trying subset multiple times
    // ex) {1,2,3} {4,5} doesnt work! but will try {2,1,3} again!
    // why hard to detect? Subset could be fine, comb of subset might wrong and dont know
    // which subset is wrong...
    bool canPartition(vector<int> &nums, int target, int k, int curSum, int curSubsetIndex, vector<int> &subset)
    {
        if (curSubsetIndex == k - 1)
            return true;

        bool res = false;
        for (int i = 0; i < nums.size(); i++)
        {
            if (subset[i] == -1 && curSum + nums[i] <= target)
            {
                subset[i] = curSubsetIndex;
                if (curSum + nums[i] == target)
                {
                    res = canPartition(nums, target, k, 0, curSubsetIndex + 1, subset);
                }
                else
                {
                    res = canPartition(nums, target, k, curSum + nums[i], curSubsetIndex, subset);
                }
                if (res)
                    return res;
                subset[i] = -1;
            }
        }

        return false;
    }

    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int sum = 0;
        for (int num : nums)
            sum += num;
        if (sum % k != 0)
            return false;
        int target = sum / k;
        vector<int> subset(nums.size(), -1);
        return canPartition(nums, target, k, 0, 0, subset);
    }
};
