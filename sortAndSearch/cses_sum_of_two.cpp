#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

/**
 * https://cses.fi/problemset/task/1640/
 *
 * Two-sum
 * But have to return the original Index.
 * Thus, save the index value before sorting!
 */
struct Value
{
    int val;
    int idx;
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, target;
    cin >> n >> target;

    vector<Value> arr(n);

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr[i] = Value{x, i};
    }

    sort(arr.begin(), arr.end(), [](const Value &a, const Value &b)
         { return a.val < b.val; });
    int left = 0, right = n - 1;

    while (left < right)
    {
        int sum = arr[left].val + arr[right].val;
        if (sum == target)
        {
            cout << arr[left].idx + 1 << " " << arr[right].idx + 1 << "\n"; // 1-index
            return 0;
        }
        else if (sum > target)
        {
            right--;
        }
        else
        { // sum < target
            left++;
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}