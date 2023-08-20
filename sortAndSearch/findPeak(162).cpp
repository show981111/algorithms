/**
 * @brief Finding peak
 * Idea is, if mid is smaller than its neighbor, then neighbor is
 * the possible peak! => so we can use binary search
 */

class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end)
    {
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2;
        if (mid == start)
        { // mid == end? only possible when start == mid
            if (nums[mid] >= nums[end])
                return mid;
            else
                return end;
        }
        if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1])
            return mid; // found Peak

        if (nums[mid - 1] < nums[mid])
        { // peak is in the bigger side
            return binSearch(nums, mid + 1, end);
        }
        else
            return binSearch(nums, start, mid - 1);
    }
    int findPeakElement(vector<int> &nums)
    {
        return binSearch(nums, 0, nums.size() - 1);
    }
};

// 1 2 3 4 5