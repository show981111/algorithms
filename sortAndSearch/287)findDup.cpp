/**
 * @brief Think how to abandon half!!
 *  ++ without sorting
 * Various Approach!
 * We can do bin Search based on Count! not just number it self!
 * Bin search based on GUESS -> GUESS and throw away half
 * Guess MID, there must be "MID" number of elements that are <= mid.
 *
 *
 * https://leetcode.com/problems/find-the-duplicate-number/solutions/1892921/9-approaches-count-hash-in-place-marked-sort-binary-search-bit-mask-fast-slow-pointers/
 *
 * Also can view this as a cycle problem (slow, fast pointer)
 */

class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end)
    {
        if (start > end)
            return -1;

        int mid = start + (end - start) / 2;
        int l = mid - 1 >= 0 ? nums[mid - 1] : -1;
        int r = mid + 1 < nums.size() ? nums[mid + 1] : -1;
        if (nums[mid] == l || nums[mid] == r)
        {
            return nums[mid];
        }
        else if (nums[mid] >= mid + 1)
            // go right if nums[mid] - 1 < mid ?
            return binSearch(nums, mid + 1, end);
        else
        {
            // nums[mid] < mid + 1=> 있어야 할 넘보다 더 작은놈이 있네? 왼쪽에 뭔가 낄껴한것!
            return binSearch(nums, start, mid - 1);
        }
    } // For each index, index + 1 should be there
    // 0 1 2 3 4
    // 1 1 2 3 4
    int findDuplicate(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        return binSearch(nums, 0, nums.size() - 1);
    }
};

/**
 * @brief Bin Search Based on COUNT?!
 * Guess number, Count, check how many numbers are there
 * Throw away half by checking a count
 */

class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end)
    {
        if (start >= end) // Narrowed down the search range to start == end, this must be the answer!
            return start;

        int mid = start + (end - start) / 2;
        int smallerThanMid = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] <= mid)
                smallerThanMid++;
        }
        if (smallerThanMid > mid)               // there must be "mid" number of elements that are <= mid.
            return binSearch(nums, start, mid); // mid could be a redundant one.
        else
            return binSearch(nums, mid + 1, end); // all counts are correct.
    }
    // 0 1 2 3 4 OR 0 1 2 3 4
    // 1 1 2 3 4.   1 2 3 4 4
    int findDuplicate(vector<int> &nums)
    {
        return binSearch(nums, 0, nums.size() - 1);
    }
};

class Solution
{
public:
    /*
    Consider the value as a next node, and each index as a node.
    Then, we can use cycle detection algorithm!
    EX)
    [1,3,4,2,2]
    Idx: next Idx as a value
    0: 1
    1: 3
    2: 4
    3: 2
    4: 2
    0 -> 1 -> 3 -> 2 -> 4 - > 2
    */
    int findDuplicate(vector<int> &nums)
    {
        int slow = 0;
        int fast = 0;

        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];

            if (fast >= nums.size())
            {
                return -1; // no cycle
            }
        } while (slow != fast);

        // now find the entry point.
        slow = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};