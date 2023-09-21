#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * Subarray sum can be calculated by prefix in O(1)
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    unordered_map<int, long long> prefix;
    long long curSum = 0;
    prefix[-1] = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        curSum += x;
        prefix[i] = curSum;
    }

    for (int i = 0; i < q; i++)
    {
        int start, end;
        cin >> start >> end; // 1 ~ x
        cout << prefix[end - 1] - prefix[(start - 1) - 1] << "\n";
    }

    return 0;
}