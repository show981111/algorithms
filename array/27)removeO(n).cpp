/**
 * How to remove multiple elements in O(N) in array?
 *
 * Brute force - every time we see "val", erase and shift => O(N^2)
 *
 * Remove by push all elems to the end of the array
 * Managing index is a bit tricky. Think carefully for break condition
 *
 * Break condition: When currentIndex >= valStartingIndex
 * : all elems 0 ~ currentIndex should not be equal to "val"
 * If valStartingIndex <= currentIndex, then "val"'s came across the currentIndex, so all elems from currentIndex are eqaul to "val"
 *
 * Remove-Erase Idiom!
 */

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int valStartsAfter = nums.size() - 1;

        for (int i = 0; i <= valStartsAfter; i++)
        {
            if (nums[i] == val)
            {
                while (valStartsAfter >= i && nums[valStartsAfter] == val)
                {
                    valStartsAfter--;
                }
                // We already came inside of the val's range.
                // will be all equal to val after this.
                if (valStartsAfter < i)
                    break;
                swap(nums[i], nums[valStartsAfter]);
                valStartsAfter--;
            }
        }

        return valStartsAfter + 1; // since 0-index!
    }
};

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        auto iter = remove(nums.begin(), nums.end(), val);
        // returns the start index of val's
        return iter - nums.begin();
    }
};