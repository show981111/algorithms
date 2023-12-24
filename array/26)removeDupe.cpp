/**
 * Remove due in sorted array!
 *
 * Can't do BIN search because we need to remove all dups.
 * dups can be in left or can be in right.
 *
 * Thus, best case O(N)
 * keep the index of unqiuely sorted part of the array
 *
 * ex)
 * 1 1 2 3 3 4 5 6 7 7
 *   |
 * 1 2 1 3 3 4 5 6 7 7
 *     |
 * 1 2 3 1 3 4 5 6 7 7
 *       |
 * 1 2 3 1 3 4 5 6 7 7
 *       | V
 * 1 2 3 4 3 1 5 6 7 7
 *         | V
 * 1 2 3 4 5 1 3 6 7 7
 *           | V
 * 1 2 3 4 5 6 3 1 7 7
 *             | V
 * 1 2 3 4 5 6 7 1 3 7
 *               | V
 * <Unique-sorted>
 */

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        // 1 1 2 3 3 4 5 6 7 7
        // 1 2 1 3 3 4 5 6 7 7
        // 1 2 3 1 3 4 5 6 7 7
        int next = 1;       // unique elements are from 0 ~ next - 1
        int prev = nums[0]; // record prev element. Due to swap, can't use nums[cur-1]
        for (int cur = 1; cur < nums.size(); cur++)
        {
            if (nums[cur] == prev)
                continue;
            else
            {
                prev = nums[cur];
                swap(nums[next], nums[cur]); // put into the uniquely sorted part!
                next++;
            }
        }

        return next;
    }
};