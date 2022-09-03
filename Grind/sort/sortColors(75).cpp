/**
 * @brief Sort 3 colors using a inplace sort! O(N)
 * Separate three colors!
 *
 * Since we only have three items to sort,
 * we know that which item should go to the beginning (0)
 * which item should go to the end (2)
 *
 * We can separate the region by using this idea!
 */

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        /**
         * @brief Solution 1
         * before zeors, all numbers are zero
         * after twos, all numbers are two
         * zeros ~ i are ones,
         * and i ~ twos are unkown!
         *
         * i is indicating a unknown variables that should be
         * evaluated and decided to send to ones or twos
         *
         * if nums[i] == 0, we should send this to ones.
         * We know that before ones are all 0, so we swap(nums[i], nums[zeros])
         *
         * since zeros <= i, we already evaluated from 0 ~ i-1.
         * this means, there are no 2 in 0 ~ i -1 (if there is, then we must have swapped
         * and sent it to twos)
         * Thus nums[i] == 1 after swap, which is good
         *
         * If nums[i] == 2, we should send this to twos. swap(nums[i], nums[twos])
         * But, we do not know nums[twos] because we didnt evaluate it.
         * Thus, after swapping we should re-evaluate this number!
         */
        int zeros = 0;
        int twos = nums.size() - 1;
        for (int i = 0; i <= twos; i++)
        {
            if (nums[i] == 0)
            {
                swap(nums[i], nums[zeros++]);
            }
            if (nums[i] == 2)
            {
                swap(nums[i], nums[twos--]);
                i--;
                // since we do not know nums[twos] is zero or one
                // so we should re-evaluate this num!
            }
        }

        /**
         * @brief Solution 2
         * Just while loop version of solution 1
         */
        int low = 0, mid = 0, high = nums.size() - 1;
        while (mid <= high)
        {
            if (nums[mid] == 0)
            {
                swap(nums[low++], nums[mid++]);
            }
            else if (nums[mid] == 2)
            {
                swap(nums[mid], nums[high--]);
            }
            else
            {
                mid++;
            }
        }
    }
};