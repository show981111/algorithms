#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cassert>
using namespace std;

/**
 * https://cses.fi/problemset/task/2183/
 *
 * Minimum sum we cannot make from numbers!
 * We can only use numbers once. So.. maybe knapsack?
 * Knapsack = O(Max sum * n)
 *  -> T(i,j) : using 0~i_th coins, can we make sum j? -> YES/NO
 *     T(i,j) = T(i-1, j) V T(i-1, j - value[i])
 * However, seems unnecessary because we dont really need to know all numbers that can be made.
 * We just need a first number that cannot be made.
 *
 * * * * * * * * * * * * * * *
 * How about starting from the small number, accumulating sum we can make?
 *
 * Suppose using 0 ~ (i-1)_th values, we can build a sum 0 ~ K.
 * At i_th coin, we have two choices: Take it or not.
 * If we don't take, sums we can build is just 0 ~ K.
 * If we take, sums we can build is: MIN: 0 + Value[i] (only take this coin) MAX: K + Value[i] (Current maximum buildable sum + current coin)
 *
 * The key note is, we can build all values between MIN(value[i]) ~ MAX(k+value[i]) because we know that we can build 0 ~ k using previous coins,
 * we can just add current coin to each 0 , 1, 2, 3, 4, ~ K, to build 0 + Value[i], 1 + Value[i], 2 + Value[i], ... , K + Value[i].
 *
 * Now, we can check that, if 0 + Value[i] > K + 1, then we cannot build K+1 at all!
 * Since coins after I_th coin, all coins are bigger than Value[i], which means K + 1 <  0 + Value[i] <= Value[i+1], Value[i+2] ,,,
 * Thus, no way to build K + 1.
 *
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    sort(coins.begin(), coins.end());
    unsigned long maxSum = 0; // maxSum we can make!

    for (int i = 0; i < coins.size(); i++)
    {
        if (maxSum + 1 < coins[i]) // cant build maxSum + 1 at all!
        {
            cout << maxSum + 1;
            return 0;
        }
        else
        {
            maxSum += coins[i];
        }
    }
    cout << maxSum + 1;

    return 0;
}