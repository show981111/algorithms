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
 * https://cses.fi/problemset/task/1639
 * Edit Distance
 *
 * T(i,j) : a[:i] -> b[:j] min distance
 * T(i,j) = T(i-1,j) + 1 (remove a[i])
 *        = T(i-1,j-1) + 1 (replace) or +0 (if a[i] == b[j])
 *        = T(i, j-1) + 1 (add b[j])
 *
 *   0 M O V I E
 * 0 0 1 2 3 4 5
 * L 1 1
 * O 2
 * V 3
 * E 4
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    cin >> a >> b;

    vector<vector<int>> memo(a.size() + 1, vector<int>(b.size() + 1));
    for (int i = 0; i <= a.size(); i++)
    {
        memo[i][0] = i;
    }
    for (int j = 0; j <= b.size(); j++)
    {
        memo[0][j] = j;
    }
    for (int row = 1; row <= a.size(); row++)
    {
        for (int col = 1; col <= b.size(); col++)
        {
            memo[row][col] = min(memo[row - 1][col] + 1, memo[row][col - 1] + 1);
            int replaceCost = a[row - 1] == b[col - 1] ? 0 : 1;
            memo[row][col] = min(memo[row][col], memo[row - 1][col - 1] + replaceCost);
        }
    }
    cout << memo[a.size()][b.size()];
    return 0;
}