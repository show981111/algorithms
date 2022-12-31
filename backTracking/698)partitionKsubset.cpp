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
 *
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