/**
 * @brief
 * BinSearch
 * https://leetcode.com/problems/binary-search/discuss/423162/Binary-Search-101
 *
 * Include ALL possible answers when initialize lo & hi
    Don't overflow the mid calculation
    Shrink boundary using a logic that will exclude mid
    Avoid infinity loop by picking the correct mid and shrinking logic
    Always think of the case when there are 2 elements left
 */

class Solution
{
public:
    int BinaryHelper(vector<int> &nums, int start, int end, int target)
    {
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2;
        if (nums[mid] == target)
            return mid;
        else if (target < nums[mid])
        {
            end = mid - 1;
        }
        else
        { // nums[mid] < target
            start = mid + 1;
        }
        return BinaryHelper(nums, start, end, target);
    }
    int search(vector<int> &nums, int target)
    {
        return BinaryHelper(nums, 0, nums.size() - 1, target);
    }
};