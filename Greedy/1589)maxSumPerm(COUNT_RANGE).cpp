/**
 * @brief GREEDY + SORT
 * Since we can rearrange numbers as we want,
 * we can greedily choose the biggest number for the most frequent request.
 * If we have an array of "reqCount", array where i_th index is reqCount[i] times requested
 * then we can just sort reqCount and nums, then get maxSum by adding nums[i]*reqCount[i]
 *
 * BOTTLENECK : making reqCount.
 * Brute force : O(M*N) we iterate [req[0], req[1]] and do ++.
 * Can we do this in linear time?
 *
 * HINT: PREFIX
 * [x, y]
 * We can get count as a prefix sum.
 * Think [x,y] as add +1 from x and -1 from y + 1.
 * then, if we just calculate the prefix sum, then we can get the frequency.
 * https://www.youtube.com/watch?v=sb2FNlfxQpg&ab_channel=NateSantti
 * 3:30
 */

class Solution
{
public:
    const int MOD = 1000000007;

    int maxSumRangeQuery(vector<int> &nums, vector<vector<int>> &requests)
    {
        vector<int> reqCount(nums.size(), 0);
        int maxVal = 0;
        for (vector<int> &req : requests)
        {
            reqCount[req[0]]++;
            if (req[1] + 1 < nums.size())
            {
                reqCount[req[1] + 1]--;
            }
        }

        for (int i = 1; i < reqCount.size(); i++)
        {
            reqCount[i] += reqCount[i - 1];
        }

        int ans = 0;
        sort(nums.begin(), nums.end(), greater<int>());
        sort(reqCount.begin(), reqCount.end(), greater<int>());
        for (int i = 0; i < nums.size(); i++)
        {
            if (reqCount[i] == 0)
                break;
            unsigned long mul = (unsigned long)nums[i] * (unsigned long)reqCount[i];
            ans += mul % MOD;
            ans %= MOD;
        }
        return ans;
    }
};