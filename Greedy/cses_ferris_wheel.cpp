#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_set>
using namespace std;

/**
 * Greedy usually goes well with sorting.
 * However, proving why Greedy is correct is Hard.
 * Typical pattern.
 * 1) Greedy stays Ahead : at i_th choice, greedy is better than any other choices!
 * 2) Exchange : Suppose there is an optimal solution O which is different from Greedy solution, we can
 *               tweak O to get a better solution!
 * Greedy cannot backTrack -> Each Choise should be optimal!
 * Suppose there is an optimal solution O that is different from S (Greedy solution).
 * Then, we can tweak O and create O' that is better than O' !
 * Proof pattern is, Let O = {O_1, O_2 , ... , O_n} where O_i represents i_th choice.
 * and if we replace O_i with S_i, then we can get better solution!
 *
 * So this case, if we chose something (a_i, a_j) where a_(j+1) > a_j
 * and a_i + a_j < a_i + a_(j+1) < X. Since a_i+1 > a_i, and if a_i+1 + a_j+1 > X > a_i + a_j,
 * then this solution is not optimal cuz we couldve done, a_i, a_j+1 & a_i+1 & a_j
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x;

    cin >> n >> x;
    vector<int> weights(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> weights[i];
    }
    sort(weights.begin(), weights.end());

    int left = 0, right = weights.size() - 1;
    int cabin = 0;
    while (left <= right)
    {
        int sum = weights[left] + weights[right];
        if (sum > x)
        {
            cabin++;
            right--; // need to pack weight[right] alone
        }
        else
        {
            cabin++;
            left++;
            right--;
        }
    }
    cout << cabin << "\n";
    return 0;
}