/**
 * @brief Rotated Array => compare START vs MID vs END
 * Should consider all three!
 * IF START < MID, START ~ MID is sorted, turning point is at MID ~ END
 * IF START > MID, MID ~ END is sorted, turning point is at START ~ MID
 * TARGET vs START and TARGET vs END
 * Should compare target with start and end to figure out
 * where the target can be
 */

class Solution
{
public:
    int binSearchRotatedArr(vector<int> &nums, int target, int start, int end)
    {
        if (start > end)
            return -1;

        int mid = start + (end - start) / 2;
        // cout << start << " " << mid << "  " << end << endl;
        if (nums[start] == target)
            return start;
        if (nums[end] == target)
            return end;
        if (nums[mid] == target)
            return mid;
        if (nums[start] < nums[mid]) // start~mid is sorted
        {
            if (target < nums[mid])
                if (nums[start] > target) // target is in mid ~ end
                    return binSearchRotatedArr(nums, target, mid + 1, end);
                else // nums[start] <= target, target is in start ~ mid
                    return binSearchRotatedArr(nums, target, start, mid - 1);
            else // target > nums[mid], 100% in mid ~ end
                return binSearchRotatedArr(nums, target, mid + 1, end);
        }
        else
        { // nums[start] > nums[mid] 7 8 0 1 2, mid ~ end is sorted
            if (target > nums[mid])
            {
                if (nums[end] < target)
                    return binSearchRotatedArr(nums, target, start, mid - 1);
                else
                    return binSearchRotatedArr(nums, target, mid + 1, end);
            }
            else // target < nums[mid]
                return binSearchRotatedArr(nums, target, start, mid - 1);
        }
    }
    int search(vector<int> &nums, int target)
    {
        return binSearchRotatedArr(nums, target, 0, nums.size() - 1);
    }
};