#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * If I can produce (N - i) coins with minimum coin, then I can add i to it to make minimal!
 * T(N) : minimum number of coins to make N
 * coins = [x_1, x_2, ... x_m]
 * T(N) = min(T(N - x_1), T(N-x_2), ... , T(N-x_m)) + 1
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, targetSum;
    cin >> n >> targetSum;

    vector<int> coins(n);
    vector<int> memo(targetSum + 1, -1);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
        if (coins[i] <= targetSum)
            memo[coins[i]] = 1;
    }

    for (int i = 1; i <= targetSum; i++)
    {
        for (int k = 0; k < n; k++)
        {
            if (i - coins[k] >= 0 && memo[i - coins[k]] != -1)
            {
                if (memo[i] == -1)
                    memo[i] = memo[i - coins[k]] + 1;
                else
                    memo[i] = min(memo[i], memo[i - coins[k]] + 1);
            }
        }
    }

    cout << memo.back() << "\n";

    // produce a sum of money x
    // using the available coins in such a way that the number of coins is minimal.
}