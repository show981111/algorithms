/**
 * @brief Binary Search
 * The key is identify sorted part.
 * Then make decision!
 *
 * Always shrink the search based on sorted part!
 *
 * SIMPLER VERSION <using a PIVOT>
 * https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/154836/The-INF-and-INF-method-but-with-a-better-explanation-for-dummies-like-me
 * The key is rotated sorted array can be divided to two part.
 * left sorted part vs right sorted part
 * The standard is num[0] which is act as a pivot element.
 * left sorted part is all bigger than num[0].
 * right sorted part is all smaller than num[0].
 *
 * if num[mid] and target are in the same part, just proceed binSearch
 * if they are not? we should make the other part looks like sorted
 * by making -INF or +INF
 *
 * -INF .... right sorted part => whole array is sorted
 * left sorted ... +INF => whole array is sorted
 * Now we can do binary search like we did!
 */

// SIMPLER VRESION
class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end, int target)
    {
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2;
        int comparator = nums[mid];

        if ((nums[0] <= target && nums[0] <= nums[mid])  // left half
            || (nums[0] > target && nums[0] > nums[mid]) // right half
        )
        {
            comparator = nums[mid]; // target and mid is in the same side
        }
        else
        {
            if (nums[0] <= target) // target is in left half and nums[mid] is in right
            {
                comparator = INT_MAX;
            }
            else
            { // target is in right half and nums[mid] is in left
                comparator = -INT_MAX;
            }
        }
        // now normal bin Search
        if (comparator == target)
        {
            return mid;
        }
        else if (comparator > target)
        { // target is smaller than comp go left
            end = mid - 1;
        }
        else
        { // comparator < target , target is bigger go right
            start = mid + 1;
        }
        return binSearch(nums, start, end, target);
    }
    int search(vector<int> &nums, int target)
    {
        return binSearch(nums, 0, nums.size() - 1, target);
    }
};

// original
class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end, int target)
    {
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2;
        // cout << start << " " << mid << " " << end << endl;
        if (nums[mid] == target)
            return mid;
        else if (nums[start] == target)
            return start;
        else if (nums[end] == target)
            return end;
        else if (target < nums[mid])
        {
            if (nums[start] < nums[mid])
            { // start ~ mid sorted
                if (nums[start] > target)
                    return binSearch(nums, mid + 1, end, target);
                else
                    return binSearch(nums, start, mid - 1, target);
            }
            else // mid ~ end is sorted and target < nums[mid] < nums[end]
                return binSearch(nums, start, mid - 1, target);
        }
        else
        { // nums[mid] < target
            if (nums[start] < nums[mid])
            { // start ~ mid sorted, nums[start] < nums[mid] < target
                return binSearch(nums, mid + 1, end, target);
            }
            else
            {                           // mid ~ end is sorted
                if (target < nums[end]) // mid < target < end
                    return binSearch(nums, mid + 1, end, target);
                else // mid < target but target > end
                    return binSearch(nums, start, mid - 1, target);
            }
        }
    }
    int search(vector<int> &nums, int target)
    {
        return binSearch(nums, 0, nums.size() - 1, target);
    }
};

/*
The Key of binary search on sorted array is,
For Sorted part, see start and end, then exclude that part.
Thus, we can just throw away half and go to another half.

For this problem, key was,
There must be two sorted part. L~mid is sorted or mid ~ R is sorted.
and the challenge was how to select which half we should go.

For this, we can use nums[0] because the starting element of one sorted array must be
nums[0]!!

*/
class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end, int target)
    {
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2;
        if (nums[mid] == target)
            return mid;
        else
        {
            if (nums[start] < nums[end]) // start ~ end is sorted
            {
                if (nums[mid] < target) // target is bigger
                    return binSearch(nums, mid + 1, end, target);
                else
                    return binSearch(nums, start, mid - 1, target);
            }
            else
            {                         // there is a bump in the middle
                if (nums[0] > target) // target should be located after [min ~ end]
                {
                    if (nums[mid] < target) // [L, max, min, mid, target]
                        return binSearch(nums, mid + 1, end, target);
                    else
                    { // [L, min, target, mid] or [L, mid, min, target]
                        if (nums[0] <= nums[mid])
                        { // 0 ~ mid sorted
                            // [L, mid, min, target], mid is in 0 ~ MAX
                            return binSearch(nums, mid + 1, end, target);
                        }
                        else
                        {
                            // [L, min, target, mid], mid is in min ~ end
                            return binSearch(nums, start, mid - 1, target);
                        }
                    }
                }
                else
                { // target should be located [L ~ max]
                    // [L, mid,target ,max, min] or
                    // [L, target ,max, mid, min]
                    if (nums[mid] < target)
                    {
                        if (nums[0] <= nums[mid])
                        { // 0 ~ mid sorted
                            // mid is in 0 ~ MAX
                            return binSearch(nums, mid + 1, end, target);
                        }
                        else
                        {
                            // mid is in min ~ end
                            return binSearch(nums, start, mid - 1, target);
                        }
                    }
                    else // [L, target, mid , max, min, end]
                        return binSearch(nums, start, mid - 1, target);
                }
            }
        }
    }
    int search(vector<int> &nums, int target)
    {
        return binSearch(nums, 0, nums.size() - 1, target);
    }
};