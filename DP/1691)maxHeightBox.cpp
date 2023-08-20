/**
 * @file 1491)maxHeightBox.cpp
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/solutions/2059073/c-intuitive-dp-solution-using-lis/
 * Subset problem with ordering constraint? => Subsequence!
 * => LIS problem!
 *
 * Key part of this problem is we can rotate boxes -> sort each boxes dimension, so that height is the biggest
 * And, We can only stack if width_i <= width_j && length_i <= length_j && height_i <= height_j => Ordering Constraint!
 * Smaller dimension box should come after bigger one! => Increasing sequence?! => Sort!
 *
 * Now, we can pick boxes so that the sum is the biggest under the constraint!
 *
 * memo[i] = Max height of boxes that i_th element is at the top! (use 0 ~ i_th elem, but i_th is picked)
 *
 * memo[i] = height_i + max(memo[0:i-1]) => Since it is a subset, we cannot just reference memo[i-1]
 *                                          We should consider all position that box[i] can go
 *                                          To get max heights with i_th box at the top, we should iterate
 *                                          All memo[j], which means, boxes that box[j] is at the top, get the best
 *                                          deployment!
 */

class Solution
{
public:
    bool isDeployable(vector<int> &a, vector<int> &b)
    {
        return (a[0] <= b[0] && a[1] <= b[1] && a[2] <= b[2]);
    }
    int maxHeight(vector<vector<int>> &cuboids)
    {
        for (vector<int> &item : cuboids)
        {
            sort(item.begin(), item.end());
        }
        sort(cuboids.begin(), cuboids.end(), [](vector<int> &a, vector<int> &b)
             {
            if(a[2] < b[2]) return true;
            else if(a[2] == b[2] && a[1] < b[1]) return true;
            else if(a[1] == b[1]) return a[0] < b[0];
            return false; });
        vector<int> memo(cuboids.size(), 0);
        memo[0] = cuboids[0][2]; // make max elem to be a height!
        int ans = memo[0];
        for (int i = 1; i < memo.size(); i++)
        {
            memo[i] = cuboids[i][2]; // at least we can put one
            for (int j = 0; j < i; j++)
            {
                if (isDeployable(cuboids[j], cuboids[i]))
                {
                    memo[i] = max(memo[i], cuboids[i][2] + memo[j]);
                }
            }
            ans = max(ans, memo[i]);
        }

        return ans;
    }
};