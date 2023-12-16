/**
 * 3sum
 * Fix one value, then two sum!
 *
 * Tricky part: How to remove redundancy?
 * 1) For a pviot at i_th index, run two some in [i+1:] -> Avoid using the pivot twice
 * 2) Skip redundant pivot using nums[i] == nums[i - 1] => Avoid using the same number as a pivot
 * 3) After we add a triplet, do left++ and right-- until we get the different numbers
 *
 */

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        // brute force -> all possible triplets O(N^3)
        vector<vector<int>> v;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++)
        {
            if (i != 0 && nums[i] == nums[i - 1])
            {
                continue;
            }

            int target = nums[i];
            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (target + sum == 0)
                {
                    v.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                    while (left + 1 < nums.size() && nums[left] == nums[left - 1]) // avoid redundancy!
                    {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right + 1])
                    {
                        right--;
                    }
                }
                else if (target + sum > 0)
                {
                    right--;
                }
                else
                { // target + sum < 0
                    left++;
                }
            }
        }

        return v;
    }
};