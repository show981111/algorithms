/**
 * @brief Its all the same with sorting rotated distinct elems.
 * But!
 * we need to take care of redundancies.
 * if, nums[left] == nums[mid]
 * This doesn't necessarily mean array is sorted.
 * ex) 5 1 5 5 or 5 5 1 5
 * So, we just dont know where to go... so just search both ways
 *
 * But if nums[left] == nums[mid] != nums[right],
 * we know left ~ mid are all the same elems. ex) 5 1 5 6 7 is impossible
 * Why? suppose there is min(peak) in left ~ mid, then, right half should be sorted.
 *  Thus, nums[right] > nums[mid]. But Since nums[mid] == nums[left], nums[right] > nums[left]
 *  which breaks the sorting cuz we have another peak from nums[right] -> nums[left] (rotated part)
 * So, go right!
 */

class Solution
{
public:
    bool binSearch(vector<int> &nums, int left, int right, int target)
    {
        if (right < left)
            return false;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return true;

        if (nums[left] < nums[mid])
        { // left ~ mid sorted
            if (target >= nums[left] && target < nums[mid])
            {
                return binSearch(nums, left, mid - 1, target);
            }
            else
                return binSearch(nums, mid + 1, right, target);
        }
        else if (nums[right] > nums[mid])
        { // right is sorted
            if (target > nums[mid] && target <= nums[right])
            {
                return binSearch(nums, mid + 1, right, target);
            }
            else
                return binSearch(nums, left, mid - 1, target);
        }
        else
        {                                 // nums[left] == nums[mid]
            if (nums[mid] == nums[right]) // one half must contain all nums[mid]!..
            // so dont know where to go. ex) 5 1 5 5 or 5 5 1 5 both possible
            {
                if (binSearch(nums, mid + 1, right, target))
                    return true;
                else if (binSearch(nums, left, mid - 1, target))
                    return true;
                else
                    return false;
            }
            else
            {
                // nums[mid] != nums[right] means left ~ mid are all the same
                // go right!
                return binSearch(nums, mid + 1, right, target);
            }
        }
    }
    bool search(vector<int> &nums, int target)
    {
        return binSearch(nums, 0, nums.size() - 1, target);
    }
};