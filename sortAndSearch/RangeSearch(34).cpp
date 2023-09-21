/**
 * @brief Range Search repatory
 * Compare to mid vs mid-1 and mid vs mid + 1!
 * -> algo1 look firstBadVersion
 * Since we are using a MID, in all cases, log(n)
 * even tho we have [3,3,3,3,3,3,3,3,3 ... ]
 * We proceed by n/2 since we only seach mid ~ end or start ~ mid!
 */

class Solution
{
public:
    void searchHelper(vector<int> &nums, int target, int start, int end, vector<int> &res)
    {
        if (start > end) // start can be equal to end! so we should use ">"
            return;
        int mid = start + (end - start) / 2;
        if (nums[mid] > target)
            searchHelper(nums, target, start, mid - 1, res);
        else if (nums[mid] < target)
            searchHelper(nums, target, mid + 1, end, res);
        else
        { // nums[mid] == target
            if ((mid == 0 && mid + 1 >= nums.size()) ||
                ((mid == 0 || nums[mid - 1] < nums[mid]) &&
                 (mid + 1 >= nums.size() || nums[mid + 1] > nums[mid])))
            {
                res[0] = mid;
                res[1] = mid;
                return;
            }
            else if (mid == 0 || nums[mid - 1] < nums[mid]) // found starting point
            {
                res[0] = mid;
                searchHelper(nums, target, mid + 1, end, res); // now find endpoint
                return;
            }
            else if (mid + 1 >= nums.size() || nums[mid + 1] > nums[mid]) // found endPoint
            {
                res[1] = mid;
                searchHelper(nums, target, start, mid - 1, res); // go find startPoint
                return;
            }
            searchHelper(nums, target, start, mid - 1, res);
            searchHelper(nums, target, mid + 1, end, res);
        }
    }
    vector<int> searchRange(vector<int> &nums, int target)
    {
        vector<int> res = {-1, -1};
        searchHelper(nums, target, 0, nums.size() - 1, res);
        return res;
    }
};

/*
 * Simplified. Just do twice!
 */
class Solution
{
public:
    int binSearch(vector<int> &nums, const int offset, int start, int end, int target)
    {
        if (start > end)
            return -1;
        // cout << start << " " << end << endl;
        int mid = start + (end - start) / 2;
        if (nums[mid] == target && ((mid == 0 && offset < 0) || (mid == nums.size() - 1 && offset > 0) || nums[mid + offset] != target))
        {
            return mid;
        }
        else if (nums[mid] == target && nums[mid + offset] == target)
        {
            if (offset > 0)
            {
                return binSearch(nums, offset, mid + 1, end, target);
            }
            else
                return binSearch(nums, offset, start, mid - 1, target);
        }
        else if (nums[mid] < target)
        {
            return binSearch(nums, offset, mid + 1, end, target);
        }
        else
        {
            return binSearch(nums, offset, start, mid - 1, target);
        }
    }
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int start = binSearch(nums, -1, 0, nums.size() - 1, target);
        int end = binSearch(nums, 1, 0, nums.size() - 1, target);
        vector<int> ans = {start, end};
        return ans;
    }
};