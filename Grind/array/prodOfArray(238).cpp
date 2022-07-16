/**
 * @brief O(N) algo without using a division operation
 * We have arrays that stores the result of accumulated multiplies
 * PREFIX and SUFFIX!!
 * => Big Hint
 *
 * [ .... X .... ]
 * ans[X] = nums[0:X-1] * nums[X+1:]
 *          Prefix        Suffix
 */

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        vector<int> prefix(nums.size(), 1);
        vector<int> suffix(nums.size(), 1);
        prefix[0] = nums[0];
        suffix.back() = nums.back();

        for (int i = 1; i < nums.size(); i++)
        {
            prefix[i] = nums[i] * prefix[i - 1];
        }
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            suffix[i] = nums[i] * suffix[i + 1];
        }

        vector<int> ans(nums.size());
        ans[0] = suffix[1];
        ans.back() = prefix[prefix.size() - 2];

        for (int i = 1; i < ans.size() - 1; i++)
        {
            ans[i] = prefix[i - 1] * suffix[i + 1];
        }
        return ans;
    }
};

/**
 * @brief Better
 * Time: O(N), Space: O(1) without answer array
 *
 */

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        vector<int> ans(nums.size(), 1);

        int prefix = 1;
        for (int i = 1; i < ans.size(); i++)
        {
            prefix *= nums[i - 1];
            ans[i] = prefix;
        }

        int suffix = 1;
        for (int i = ans.size() - 2; i >= 0; i--)
        {
            suffix *= nums[i + 1];
            ans[i] *= suffix;
        }

        return ans;
    }
};