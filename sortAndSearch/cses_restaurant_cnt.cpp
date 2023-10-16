#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * https://cses.fi/problemset/task/1619
 *
 * Count maximum overlapped intervals!
 *
 * Think about the impact of each interval.
 * Customer came in. At star time, it will do +1.
 *          leave, at end time it will do -1.
 * If we just iterate from the beginning and calculate prefix sum,
 * we can get the maximum number of customers present in that time!
 */

struct TimePoint
{
    int time;   // for that time
    int offset; // customer came in (+1) or out (-1)
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<TimePoint> v;
    for (int i = 0; i < n; i++)
    {
        int s, e;
        cin >> s >> e;
        v.push_back({s, 1});
        v.push_back({e, -1});
    }
    sort(v.begin(), v.end(), [](const TimePoint &a, const TimePoint &b)
         { return a.time < b.time; });
    int customerSoFar = 0;
    int maxCustomer = 0;
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        customerSoFar += iter->offset;
        maxCustomer = max(maxCustomer, customerSoFar);
    }

    cout << maxCustomer << "\n";
    return 0;
}