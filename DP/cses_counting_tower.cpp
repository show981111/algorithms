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
 * https://cses.fi/problemset/task/2413
 * Counting Towers
 *
 *
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MOD = 1e9 + 7;
    int T;
    cin >> T;

    vector<vector<unsigned long>> memo(1e6 + 1, vector<unsigned long>(2));
    memo[1][0] = 1; // width = 2
    memo[1][1] = 1; // width = 1
    int top = 2;
    for (int i = 0; i < T; i++)
    {
        int n;
        cin >> n;
        if (n < top)
        {
            cout << (memo[n][0] + memo[n][1]) % MOD << "\n";
            continue;
        }

        for (int height = top; height <= n; height++)
        {
            memo[height][0] = (2 * memo[height - 1][0] + memo[height - 1][1]) % MOD;
            memo[height][1] = (memo[height - 1][0] + 4 * memo[height - 1][1]) % MOD;
        }
        cout << (memo[n][0] + memo[n][1]) % MOD << "\n";
        top = n + 1;
    }

    return 0;
}