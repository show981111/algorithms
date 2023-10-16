#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * https://cses.fi/problemset/task/1746/
 *
 * Decision Tree based BackTracking -> TLE O(M^N), at each cell, max possibilities (1 ~ M) and there are total N cells
 *
 * How to make backtrack faster? -> MEMOIZATION
 *
 * How to find which one we are double counting? Are we revisiting the same status of recursive call?
 * Draw a sample decision tree.
 *
 * T(v, i) : # possible arrays when ith cell has a value v
 * T(v, i) = T(v - 1, i - 1) + T(v, i - 1) + T(v + 1, i - 1) // Sum up Count of previous cell ends with v - 1, v , v + 1
 *
 * If nums[i] == 0:
 *    For all v' in [1,m], if T(v', i - 1) != 0, T(v' + 1, i) += T(v', i - 1),
 *                                               T(v', i)     += T(v', i - 1),
 *                                               T(v' - 1, i) += T(v', i - 1)
 *                                              If prev cell can be end with v', then i_th cell can be v'+1, v', v'-1
 * If nums[i] != 0:
 *    i_th cell's value is fixed.
 *    Therefore, T(v, i) += T(v - 1, i - 1)
 *                       += T(v, i - 1)
 *                       += T(v + 1, i - 1)
 *              Prev cell should be v - 1, v, or v + 1 to end up with v at i_th cell.
 *
 * Now, at the end, we can sum up T(v', N) for v' in [1,m] then that is the total number of possible arrays!
 */

const int MOD = 1e9 + 7;

void backTrack(vector<int> &nums, int curIndex, int m, int lowerBound, int upperBound, unsigned long &cnt)
{
    // cout << curIndex << " " << lowerBound << " " << upperBound << endl;
    if (curIndex >= nums.size())
    {
        cnt = (cnt + 1) % MOD;
        return;
    }
    if (nums[curIndex] != 0 && curIndex > 0 && abs(nums[curIndex - 1] - nums[curIndex]) <= 1)
    {
        cnt = (cnt + 1) % MOD;
        return;
    }
    else if (nums[curIndex] != 0)
    {
        return;
    }

    vector<int> possibleVals;
    for (int i = lowerBound; i <= upperBound; i++)
    {
        possibleVals.push_back(i);
    }

    for (int i = 0; i < possibleVals.size(); i++)
    {
        nums[curIndex] = possibleVals[i];
        int lb = max(1, possibleVals[i] - 1);
        int ub = min(possibleVals[i] + 1, m);
        backTrack(nums, curIndex + 1, m, lb, ub, cnt);
        nums[curIndex] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    unsigned long ans = 0;
    vector<vector<unsigned long>> memo(m + 1, vector<unsigned long>(n, 0));

    for (int i = 0; i < n; i++)
    {
        // cout << i << " - ";
        if (nums[i] == 0)
        {
            if (i - 1 >= 0)
            {
                for (int possibleNum = 1; possibleNum <= m; possibleNum++)
                {
                    if (memo[possibleNum][i - 1] != 0)
                    {
                        if (possibleNum - 1 >= 1)
                            memo[possibleNum - 1][i] = (memo[possibleNum - 1][i] + memo[possibleNum][i - 1]) % MOD;
                        memo[possibleNum][i] = (memo[possibleNum][i] + memo[possibleNum][i - 1]) % MOD;
                        if (possibleNum + 1 <= m)
                            memo[possibleNum + 1][i] = (memo[possibleNum + 1][i] + memo[possibleNum][i - 1]) % MOD;
                    }
                }
            }
            else
            {
                for (int possibleNum = 1; possibleNum <= m; possibleNum++)
                {
                    memo[possibleNum][i] = 1;
                }
            }
        }
        else
        {
            if (i - 1 >= 0)
            {
                if (nums[i] - 1 >= 1)
                    memo[nums[i]][i] = (memo[nums[i]][i] + memo[nums[i] - 1][i - 1]) % MOD;
                memo[nums[i]][i] = (memo[nums[i]][i] + memo[nums[i]][i - 1]) % MOD;
                if (nums[i] + 1 <= m)
                    memo[nums[i]][i] = (memo[nums[i]][i] + memo[nums[i] + 1][i - 1]) % MOD;
            }
            else
            {
                memo[nums[i]][i] = 1;
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        ans = (ans + memo[i][n - 1]) % MOD;
    }

    cout << ans;

    return 0;
}