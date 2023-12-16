/**
 * Easier as 3sum cuz we dont have to check redundancy.
 *
 * Two pointer
 * 1) Sum == target -> return
 * 2) Sum > target -> right-- : All we have to do is reduce sum. If Sum gets larger, current sum is the closest to target.
 * 3) Sum < target -> left++ : Need to increase the Sum so that it can go close to target.
 */

class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int closestSum = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size() - 2; i++)
        {
            int pivot = nums[i];
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int sum = pivot + nums[left] + nums[right];

                if (abs(target - sum) < abs(closestSum - target))
                {
                    closestSum = sum;
                }
                if (sum == target)
                    return target;
                else if (sum > target)
                {
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }
        return closestSum;
    }
};