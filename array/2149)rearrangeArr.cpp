/**
 * Placing and swapping each element in arr
 * if it gets complicated, just create a temp array and place over there. This way we don't
 * modify values in-place.
 */

class Solution
{
public:
    vector<int> rearrangeArray(vector<int> &nums)
    {
        vector<int> arr(nums.size());
        int posIdx = 0, negIdx = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] >= 0)
            {
                arr[posIdx] = nums[i];
                posIdx += 2;
            }
            else
            {
                arr[negIdx] = nums[i];
                negIdx += 2;
            }
        }
        return arr;
    }
};
/**
 * In-place approach can work if the order doesn't matter
 */
class Solution
{
public:
    vector<int> rearrangeArray(vector<int> &nums)
    {
        int negIdx = 1, posIdx = 0;

        while (1)
        {
            while (posIdx < nums.size() && nums[posIdx] >= 0)
            {
                posIdx += 2;
            }
            // now nums[posIdx] < 0 or poxIdx >= nums.size
            while (negIdx < nums.size() && nums[negIdx] < 0)
            {
                negIdx += 2;
            }
            if (posIdx >= nums.size() && negIdx >= nums.size())
                break;
            swap(nums[posIdx], nums[negIdx]);
            // this will mix up the order. Neg number that comes first
            // can get swapped with pos int that is at the far end
            // EX) [-26,-37,-10,-9,15,14,31,5] => [14,-37,5,-9,15,-26,31,-10]
        }
        return nums;
    }
};