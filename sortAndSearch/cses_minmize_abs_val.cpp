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
 * https://cses.fi/problemset/task/1074
 *
 * Minimizing sum of absolute values
 *
 * MINIMIZE |x - a_1| + |x - a_2| + ... + |x - a_n|
 *
 * Absolute Values = Distance! from that point
 * Median is OPT
 *
 * . . . . . . . . . .  .  .
 * 1 2   4         9 10
 *       ^ (median)
 * If we move ^ to right, we will get +1 from 1, +1 from 2, (+1) from 4, (-1) from 9, (-1) from 10, so total +1!
 *                 left, we will get -1, -1, +1 ,+1 ,+1 from (1,2,4,9,10) so total +1!
 * => Thus median is optimal. It is all about offset and number of nodes we are getting far away from!
 *
 * If n = Even
 * . . . . . . . . . .  .  .
 * 1 2   4     7   9 10
 *       ^ ^ ^ ^
 * Anything between two middle values can be an Optimal value!
 * From 4, If we move right, we are moving away from (1,2,4) but getting close to (7,9,10) so offset = 0
 * However, if we move left, we are moving closer to (1,2) but moving away from (4,7,9,10) sp offset = +1
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> sticks(n);
    for (int i = 0; i < n; i++)
    {
        cin >> sticks[i];
    }

    sort(sticks.begin(), sticks.end());
    int med = sticks[sticks.size() / 2];
    unsigned long sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (med > sticks[i] ? med - sticks[i] : sticks[i] - med);
    }
    cout << sum;

    return 0;
}