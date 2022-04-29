#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int insertHelper(vector<int> &nums, int start, int end, int target)
    {
        if (start > end)
            return start;
        int mid = start + (end - start) / 2;
        if (nums[mid] == target)
        {
            return mid;
        }
        if (nums[mid] < target)
            return insertHelper(nums, mid + 1, end, target);
        else
            return insertHelper(nums, start, mid - 1, target);
    }
    int searchInsert(vector<int> &nums, int target)
    {
        return insertHelper(nums, 0, nums.size() - 1, target);
    }
};