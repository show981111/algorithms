#include <iostream>
#include <vector>

using namespace std;
class Solution
{
public:
    int BinaryHelper(vector<int> &nums, int start, int end, int target)
    {
        if (start > end)
            return -1;
        int mid = (end + start) / 2;
        if (nums[mid] == target)
        {
            return mid;
        }
        if (nums[mid] < target)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
        return BinaryHelper(nums, start, end, target);
    }
    int search(vector<int> &nums, int target)
    {
        return BinaryHelper(nums, 0, nums.size() - 1, target);
    }
};