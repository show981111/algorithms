#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <map>
#include <unordered_set>
using namespace std;

/**
 * Since 2 + 3 + 5, 2 + 5 + 3 are distinct in this case, we can just this approach.
 * ex) T(10) = T(5) + T(7), and T(7) has 2 + 5 T(5) has 2 + 3, so it gives us permutation not the combination
T(x) = #ways to make sum x using all coins
T(X) = Sum(T(X - coins[i])) (i = 0 ~ n)
base case: T(0) = 1, not using any coins, can make sum 0
 */

int main()
{
    int mod = 1e9 + 7;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x;

    cin >> n >> x;
    vector<int> coins(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    vector<unsigned int> memo(x + 1, 0);
    memo[0] = 1;

    for (int i = 1; i <= x; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i - coins[j] >= 0)
            {
                memo[i] = (memo[i] + memo[i - coins[j]]) % mod;
            }
        }
    }

    cout << memo[x] << "\n";
    return 0;
}