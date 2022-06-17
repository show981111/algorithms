/**
 * @brief DP
 * T(n) = max(T(n-1), T(n-2) ... T(0)) + 1
 * T(n) = max(이전것들 중 n번쨰 것보다 작은거 + 1)
 * EX)
 * [0,1,0,3,2,3]
 *  1 2 1 3 3 4 => memo
 */

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        vector<int> memo(nums.size());
        memo[0] = 1;
        int ans = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            int maxLeng = 1;
            for (int k = i - 1; k >= 0; k--)
            {
                if (nums[k] < nums[i] && maxLeng < memo[k] + 1) // find the element that is smaller that current element
                    maxLeng = memo[k] + 1;                      // pick the biggest one
            }
            memo[i] = maxLeng;
            if (maxLeng > ans)
                ans = maxLeng;
        }
        // for(auto i : memo)
        //     cout << i << ' ';
        // cout << endl;
        return ans;
    }
};