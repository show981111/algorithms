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
 * 1) O(nlogn) + O(mlogn) using MAP!
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;

    cin >> n >> m;

    map<int, int> prices;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        prices[x]++;
    }
    // 3 5 5 7 8
    for (int i = 0; i < m; i++)
    {
        int bid;
        cin >> bid;
        auto iter = prices.lower_bound(bid);

        // if iter == prices.end() => all elems < val

        if (iter == prices.end() || iter->first > bid)
        {
            if (iter != prices.begin())
            {
                iter = prev(iter);
            }
            else
                iter = prices.end();
        }
        if (iter != prices.end() && iter->second > 0)
        {
            bid = iter->first;
            iter->second--;
            if (iter->second == 0)
            {
                prices.erase(iter->first);
            }
        }
        else
        {
            bid = -1;
        }

        cout << bid << "\n";
    }

    return 0;
}