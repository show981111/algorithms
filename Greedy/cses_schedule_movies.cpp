#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * https://cses.fi/problemset/task/1629
 *
 * Why selecting earliest end is optimal?
 *  -> If we select that ends later, than we have smaller time window to
 *     choose possible movies.
 */

struct Interval
{
    int start;
    int end;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<Interval> movies(n);
    for (int i = 0; i < n; i++)
    {
        cin >> movies[i].start >> movies[i].end;
    }

    sort(movies.begin(), movies.end(), [](const Interval &a, const Interval &b)
         { return a.end < b.end; });

    int numberOfMovies = 0;
    int cur = 0;
    int prevEnd = -1;

    while (cur < movies.size())
    {
        if (movies[cur].start >= prevEnd)
        {
            numberOfMovies++;
            prevEnd = movies[cur].end;
        }
        cur++;
    }

    cout << numberOfMovies;

    return 0;
}