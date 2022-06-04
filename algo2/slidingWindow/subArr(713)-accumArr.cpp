class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        const int N = nums.size();
        for (int i = 1; i < N; i++)
        {
            nums[i] *= nums[i - 1]; // int overflow due to this process
            // cout << nums[i] << " ";
        }
        int count = 0;

        for (int i = -1; i < N; i++)
        {
            int denom = i == -1 ? 1 : nums[i];
            // cout << endl;
            for (int j = i + 1; j < N; j++)
            {
                // cout << nums[j]/denom << " ";
                if ((nums[j] / denom) < k)
                {
                    count++;
                }
            }
        }
        return count;
    }
};