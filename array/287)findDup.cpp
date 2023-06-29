/**
 * @brief Find dup
 * Need a lil trick.
 * Problem)
 * Given an array of integers nums
 * containing n + 1 integers where each integer is in the range [1, n] inclusive.
 *
 * Biggest hint is [1,n] inclusive. Is there a way we can mark which numbers are used
 * without using extra spaces? since each num are [1,n], we can just make elems negative
 * to mark it! Also, since [1,n], we dont need to use map, just use array! and we alr have array
 * that is given from parameter!
 *
 * When the key is unsigned int, dont use map, just use array and utilize index!
 */

class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            int num = nums[i];
            if (num < 0)
                num = -num;
            int checkIndex = num - 1;
            if (nums[checkIndex] < 0)
                return num;
            else
                nums[checkIndex] = -nums[checkIndex];
        }
        /* [1,3,4,2,2]
        [-1,3,4,2,2], [-1,3,-4,2,2], [-1,3,-4,-2,2]
        */
        return 0;
    }
};