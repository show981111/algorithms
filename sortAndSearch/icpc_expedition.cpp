#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/**
 * https://codeforces.com/group/62c8bIEN9G/contest/474705/problem/B
 *
 * How do we get the maximum?
 * Greedy or DP... unless we do exhaustive search.
 *
 * Best way we can do is, we distribute the food type that has the biggest amount.
 * => utilize the biggest amount resource because that has the most potential.
 *
 */
struct Info
{
    int type;
    int cnt;
};
bool canFeed(int days, vector<Info> &foods, int total)
{
    int needToFill = total;
    for (int i = 0; i < foods.size(); i++)
    {
        if (foods[i].cnt >= days * needToFill) // can fullfull what we need for n days with this food type
        {
            return true;
        }
        else
        {
            int canFullFill = foods[i].cnt / days;
            needToFill -= canFullFill; // unless, fill as much we can
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;

    cin >> n >> m;
    unordered_map<int, int> typeCount;
    vector<Info> foods;

    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        typeCount[x]++;
    }
    for (auto iter : typeCount)
    {
        foods.push_back({iter.first, iter.second});
    }
    sort(foods.begin(), foods.end(), [](const Info &a, const Info &b)
         { return a.cnt > b.cnt; });

    int days = 1;
    while (canFeed(days, foods, n))
    {
        days++;
    }
    cout << days - 1 << "\n";
    return 0;
}