#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

/**
 * https://cses.fi/problemset/task/1133/
 *
 * Binary Lifing
 *
 * How to make O(N) searching to O(logN)?
 * (1) Divid By Two : Binary Search or Divide & Conquer -> Can't use this case. Can't do random access.
 * (2) Power Of Two : Make a quick access pointer(shortcut) at each power of two points
 *                    ex) Binary Tree, Segment Tree, Sparse Tables
 *
 * For each node, record the 2^i_th ancestor.
 * For general k_th ancestor, max O(log(level)) since we can perform number of 1's amount of look up in binary representation.
 * EX) x's 17_th ancestor: 17 = 10001 -> 2^4 + 2^0 (Two look up: x's 1_th ancestor = y. y's 16_th ancestor = z -> answer)
 *
 * Preprocessing: Record all power of two ancestor -> O(N*log(h))
 * Recurrence Relation
 *      bosses[cur][j] 2^j th boss of cur = bosses[bosses[cur][j-1]][j-1] Why? 2^j - 2^j-1 = 2^j-1(2 - 1) = 2^( j - 1)
 *
 * Some Bit Manipulation
 * (1) LSB: X & -X
 * (2) POWER of Two? : n % (n - 1) == 0
 */

void dfs(vector<vector<int>> &graph, vector<vector<int>> &bosses, int cur, int prev, int level)
{
    bosses[cur][0] = prev;

    // (n & (n - 1)) == 0

    int powerOfTwo = 2;
    int power = 1;
    while (powerOfTwo <= level)
    {
        bosses[cur][power] = bosses[bosses[cur][power - 1]][power - 1];
        power++;
        powerOfTwo = powerOfTwo << 1;
    }

    for (int child : graph[cur])
    {
        if (child == prev)
            continue;

        dfs(graph, bosses, child, cur, level + 1);
    }
}

int lookUp(vector<vector<int>> &bosses, int cur, int level)
{
    int power = 0;
    // cout << cur << " : " << level << endl;
    while (level > 0)
    {
        if (level % 2 == 1)
        {
            // cout << cur << " -> " << power << endl;
            cur = bosses[cur][power];
            if (cur == -1)
                return -1;
            // cout << cur << " p: " << power << endl;
        }
        power++;
        level = level >> 1;
    }

    return cur;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;

    // vector<int> parent(n + 1);
    vector<vector<int>> graph(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;
        graph[p].push_back(i);
        graph[i].push_back(p);
    }
    // int N = ceil(log2(n));
    vector<vector<int>> bosses(n + 1, vector<int>(20, -1));
    dfs(graph, bosses, 1, -1, 0);

    for (int i = 0; i < q; i++)
    {
        int from, level;
        cin >> from >> level;
        cout << lookUp(bosses, from, level) << "\n";
    }
    return 0;
}