/**
 * Two sum variation.
 * Typical, sort and use two pointers to count the pairs!
 * Starting from the each end and go to middle!
 */
class Solution
{
public:
    int maxOperations(vector<int> &nums, int k)
    {
        int pairs = 0;
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int sum = nums[left] + nums[right];

            if (sum == k)
            {
                pairs++;
                left++;
                right--;
            }
            else if (sum > k)
            {
                right--; // gotta make sum smaller!
            }
            else
            {           // sum < k
                left++; // gotta make sum bigger!
            }
        }
        return pairs;
    }
};