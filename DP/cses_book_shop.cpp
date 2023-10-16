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
 * T(i , p): Maximum number of pages we can get from choosing 0 ~ i_th books and with cost "p"
 * T(i , p) = max(T(i - 1, p - price[i]) + page[i], T(i, p - 1), T(i-1, p)) [Buy current one, or not buy]
 *                   Buy current                     Dont buy current and get most
 * Base case T(0,0) = T(0, price[0] <= p) = page[0]
 *
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, maxPrice;
    cin >> n >> maxPrice;

    vector<int> prices(n);
    vector<int> pages(n);

    for (int i = 0; i < n; i++)
    {
        cin >> prices[i]; // restriction
    }

    for (int i = 0; i < n; i++)
    {
        cin >> pages[i]; // maximize
    }

    vector<vector<int>> memo(n, vector<int>(maxPrice + 1, 0));
    for (int i = prices[0]; i <= maxPrice; i++)
    {
        memo[0][i] = pages[0];
    }

    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= maxPrice; j++)
        {
            memo[i][j] = max(memo[i][j - 1], memo[i - 1][j]);
            if (j - prices[i] >= 0)
            {
                memo[i][j] = max(memo[i][j], memo[i - 1][j - prices[i]] + pages[i]);
            }
            ans = max(memo[i][j], ans);
            // cout << memo[i][j] << " ";
        }
        // cout << endl;
    }
    cout << ans;
    return 0;
}