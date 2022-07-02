/**
 * @brief Using a Pair
 * We sort the vector of pair. THen, using a two pointer!
 *
 * Time : O(nlogn), Space : O(n)
 */

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<pair<int, int>> numsWithIndex(nums.size());
        for (int i = 0; i < nums.size(); i++)
            numsWithIndex[i] = {nums[i], i};

        sort(numsWithIndex.begin(), numsWithIndex.end(), [](pair<int, int> &r, pair<int, int> &l)
             { return r.first < l.first; });
        int left = 0, right = numsWithIndex.size() - 1;

        while (left < right)
        {
            int sum = numsWithIndex[left].first + numsWithIndex[right].first;

            if (sum == target)
            {
                return {numsWithIndex[left].second, numsWithIndex[right].second};
            }
            else if (sum > target)
                right--;
            else
                left++;
        }
        return vector<int>();
    }
};

/**
 * @brief HashMap
 * We can save the number to the map and just try to find the residue
 * as we traverse the array!
 * Time : O(n), Space : O(n)
 */

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> mp;

        for (int i = 0; i < nums.size(); i++)
        {
            if (mp.find(target - nums[i]) != mp.end())
            {
                return {mp[target - nums[i]], i};
            }
            else
            {
                mp[nums[i]] = i;
            }
        }
        return vector<int>();
    }
};