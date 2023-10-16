#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

/**
 * https://cses.fi/problemset/task/1637
 *
 * Get maximum number of operation
 * (1) Greedy (2) DP (3) Complete search using backtrack.
 *
 * For N = ABCD, we have number of choices
 * N - A, N - B, N - C, N - D
 * It is a decision tree until it reaches 0.
 *
 * So the brute force would be using backtracking.
 * Then, why don't we try DP using a memo?
 *
 * For N = ABCD, T(N) = min(T(N-A),T(N-B),T(N-C),T(N-D)) + 1
 *
 * (*) Greedy: Subtract Biggest Digit Each Time.
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<int> memo(n + 1, INT_MAX);

    for (int i = 1; i <= min(9, n); i++)
    {
        memo[i] = 1;
    }
    for (int i = 10; i <= n; i++)
    {
        int temp = i;
        int maxD = 0;
        while (temp > 0)
        {
            int d = temp % 10;
            maxD = max(d, maxD);
            if (d > 0)
                memo[i] = min(memo[i], memo[i - d] + 1);
            temp /= 10;
        }

        if (memo[i - maxD] + 1 != memo[i])
        {
            cout << i << " max " << maxD << " not working!\n";
        }
    }

    // Greedy
    // int op = 0;
    // while (n > 0)
    // {
    //     int temp = n;
    //     int maxD = 0;
    //     while (temp > 0)
    //     {
    //         int d = temp % 10;
    //         maxD = max(d, maxD);
    //         temp /= 10;
    //     }
    //     op++;
    //     n = n - maxD;
    // }
    // cout << op;
    cout << memo.back();

    return 0;
}