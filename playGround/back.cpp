#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * Restriction & Max result from all Subsets => KNAPSACK
 *
 *
 * T(i , p): Maximum number of pages we can get from choosing 0 ~ i_th books and with cost "p"
 * T(i , p) = max(T(i - 1, p - price[i]) + page[i], T(i, p - 1), T(i-1, p)) [Buy current one, or not buy]
 *                   Buy current                     Dont buy current and get most
 * Base case T(0,0) = T(0, price[0] <= p) = page[0]
 *
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

    for (int i = 0; i < n;)
    {
        int zeroInd = -1;
        while (i < n && nums[i] == 0)
        {
            if (zeroInd == -1)
                zeroInd = i;
            i++;
        }

        if (zeroInd == -1)
            i++;
        else
        {
            int lb = 1;
            int ub = m;

            if (i < n)
            {
                lb = max(1, nums[i] - (i - zeroInd));
                ub = min(ub, nums[i] + (i - zeroInd));
            }
            if (zeroInd - 1 >= 0)
            {
                lb = max(lb, nums[zeroInd - 1] - 1);
                ub = min(ub, nums[zeroInd - 1] + 1);
            }
            unsigned long cnt = 0;
            backTrack(nums, zeroInd, m, lb, ub, cnt);
            // cout << lb << " " << ub << " " << cnt << endl;
            // cout << cnt << " ";

            if (ans == 0)
                ans = (ans + cnt) % MOD;
            else
            {
                ans = (ans * cnt) % MOD;
            }
        }
    }

    cout << ans;

    return 0;
}