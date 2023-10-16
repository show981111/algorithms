#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

/**
 * https://cses.fi/problemset/task/1643/
 *
 * MAX Subarray Sum!
 *
 * Use prefix sum to get the max!
 *
 * If prefix < 0 -> Negative effect to subarray sum. it is better to start new if new val is bigger!
 * If prefix >= 0 -> Positive effect, to keep the prefix, keep accumulating!
 *
 * DP approach!!
 *
 * Consider, subarray that ends at "K"_th position. like LIS.
 * - 1. Just K_th elem.
 * - 2. subarray sum that ends at "K-1"_th position + arr[K]
 * => Let, T(N) be the max subarray sum that ends at N.
 * T(N) = max(arr[N], T(N-1) + arr[N])
 *
 * Max subarray sum of this array (Answer) = max(T(1) ... T(N))
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    long accumSum = 0;
    long maxSum = LONG_MIN;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        // if (accumSum < 0)
        // {
        //     accumSum = max(accumSum, (long)x);
        // }
        // else
        // {
        //     accumSum += x;
        // }
        // maxSum = max(maxSum, accumSum);

        // DP approach
        accumSum = max((long)x, accumSum + x);
        maxSum = max(accumSum, maxSum);
    }
    cout << maxSum;
    return 0;
}