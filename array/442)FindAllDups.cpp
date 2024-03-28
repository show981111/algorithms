/**
 * Same trick as before.
 * Leave a mark in the array while preserving the value.
 * (by just making a negative, we can revert original value with abs()).
 *
 * Not just making a negative, we can even set a certain bit at the position
 * if we utilize the maximum possible value of each element!
 */

class Solution
{
public:
    vector<int> findDuplicates(vector<int> &nums)
    {
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++)
        {
            int markIdx = abs(nums[i]) - 1;
            if (nums[markIdx] < 0)
            {
                ans.push_back(markIdx + 1);
            }
            else
            {
                nums[markIdx] = -nums[markIdx];
            }
        }
        return ans;
    }
};