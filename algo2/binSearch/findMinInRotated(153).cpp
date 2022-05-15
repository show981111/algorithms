/**
 * @brief Rotated Array
 * Always consider start vs mid vs end !!
 * Find the part that is not sorted! => Finding a turning point
 * 1 2 3 4 5 : nums[start] < nums[mid] < nums[end] => start ~ end is sorted
 * 1 2 3 4 -1 : nums[start] < nums[mid] (Start ~ mid is sorted)
 *              but nums[mid] > nums[end] => mid ~ end is not sorted
 * 5 6 -1 1 2 3 4 : nums[start] > nums[mid] => start ~ mid is not sorted
 */

class Solution
{
public:
    int findMinOnRotated(vector<int> &nums, int start, int end)
    {
        if (start > end)
            return -5001;
        int mid = start + (end - start) / 2;
        if (mid == start)
        {
            if (nums[start] >= nums[end])
                return nums[end];
            else
                return nums[start];
        }
        if (nums[mid - 1] > nums[mid])
            return nums[mid];
        else // if(nums[mid - 1] < nums[mid]) //  mid is sorted
        {
            if (nums[start] < nums[mid])
            { // start ~ mid is sorted,
                if (nums[mid] < nums[end])
                { // start ~ end is sorted
                    return nums[start];
                }
                else
                { // nums[mid] > nums[end], so right side is not sorted!
                    return findMinOnRotated(nums, mid + 1, end);
                }
            }
            else
            {                                                  // nums[start] > nums[mid]
                return findMinOnRotated(nums, start, mid - 1); // left side is not sorted
            }
        }
    }
    int findMin(vector<int> &nums)
    {
        return findMinOnRotated(nums, 0, nums.size() - 1);
    }
};