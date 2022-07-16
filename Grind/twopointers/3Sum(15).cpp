class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int N = nums.size();
        vector<vector<int>> res;
        for (int pivot = 0; pivot <= N - 3; pivot++)
        {
            if (pivot > 0 && nums[pivot] == nums[pivot - 1])
                continue; // same pivot makes redundant result!

            int left = pivot + 1;
            int right = N - 1;

            while (left < right)
            {
                int s = nums[pivot] + nums[left] + nums[right];
                if (s > 0)
                {
                    --right; // sum is too big
                }
                else if (s < 0)
                {
                    ++left; // sum is too small
                }
                else
                { // s == 0
                    res.push_back({nums[pivot], nums[left], nums[right]});
                    int leftNum = nums[left];
                    int rightNum = nums[right];

                    // skip redundant elems
                    while (left < N && nums[left] == leftNum)
                        left++;
                    while (right >= 0 && nums[right] == rightNum)
                        right--;
                }
            }
        }
        return res;
    }
};