/**
 * O(NlogN) With O(N) SC.
 * O(1) SC is hard since pushing / pulling method will cause cycle
 *
 In a sorted list.(DESCENDING)
 [6, 5, 4, 3, 2, 1]
 Need to put first half in an odd position & later half in an even position
 . 6 . 5 . 4
 3 . 2 . 1
 This way, starting from i = 0,  nums[i] >      nums[i+2] >             nums[i+4].
                         i = 1.         nums[i] <           nums[i+2] <            nums[i+4]
*/

class Solution
{
public:
    void wiggleSort(vector<int> &nums)
    {
        sort(nums.rbegin(), nums.rend());

        vector<int> ans(nums.size());
        int mid = (nums.size() / 2) - 1;
        for (int i = 0; i <= mid; i++)
        {
            ans[2 * i + 1] = nums[i];
        }
        for (int i = mid + 1; i < nums.size(); i++)
        {
            ans[2 * (i - mid - 1)] = nums[i];
        }
        nums = ans;
    }
};
