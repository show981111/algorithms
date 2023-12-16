class Solution
{
public:
    /*
        Just Like LIS.
        Since we can't know if we can form a subarray at step I or not,
        we force that the subarray includes i-1 element!
        Then, we get max from all those max Value ending at I.

        T(i) = maxSubArraySum ending with I
        T(i) = max(T(i-1) + nums[i], nums[i])
            Two choice: concatenate or start fresh
    */

    int maxSubArray(vector<int> &nums)
    {
        int maxSum = nums[0];
        int maxEndingHere = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            maxEndingHere = max(maxEndingHere + nums[i], nums[i]);
            maxSum = max(maxSum, maxEndingHere);
        }
        return maxSum;
    }
};