/**
 * Two cases
 *
 * One big magnitude negative number * Top two positive number
 * VS
 * Top three positive numbers
 *
 * Other cases will result in neg number so invalid
 */

class Solution
{
public:
    int maximumProduct(vector<int> &nums)
    {
        // int soFarMin = nums[0];
        // int soFarMax = nums[0];
        // int ans = nums[0];
        // for(auto iter = next(nums.begin()); iter != nums.end(); ++iter){
        //     int num = *iter;
        //     cout << num << " ";
        //     int tempMin = soFarMin;
        //     soFarMin = min(min(num, soFarMin), min(soFarMin*num, soFarMax*num));
        //     soFarMax = max(max(num, soFarMax), max(tempMin*num, soFarMax*num));
        // } -> Find maxProdSubset
        sort(nums.begin(), nums.end());
        int N = nums.size();
        int ans = INT_MIN;
        ans = max(ans, nums[N - 1] * nums[N - 2] * nums[N - 3]);
        // ans = max(ans, nums[N-1] * nums[N-2] *nums[0]);
        ans = max(ans, nums[N - 1] * nums[1] * nums[0]);
        // ans = max(ans, nums[2] * nums[1] *nums[0]);

        return ans;
    }
};