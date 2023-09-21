#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * Range Min or Range Max -> O(NlogN) by preprocessing every power of two length!
 * Accessing values, array is faster than unordered_map!
 *
 * table[i][j] : for length 2^i subarray, starting from j's index.
 * -> Why 2^i th subarray? -> to save memory! no need to allocate 2^i rows!
 */

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    int table[20][200003];
    long long largestWindowSize = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> table[0][i]; // length 2^0 = 1, startIndex = i
        if (i + 1 >= largestWindowSize)
            largestWindowSize = largestWindowSize << 1;
    }
    largestWindowSize = largestWindowSize >> 1;

    /**
     * Preprocessing. Bottom-up way, fill table!
     */
    long long windowSize = 2;
    int power = 1;
    while (windowSize <= largestWindowSize)
    {
        for (long long i = 0; i < n - windowSize + 1; i++)
        {
            long long mid = i + (windowSize - 1) / 2;

            int val;
            if (table[power - 1][i] == 0)
                val = table[power - 1][mid + 1];
            else if (table[power - 1][mid + 1] == 0)
                val = table[power - 1][i];
            else
                val = min(table[power - 1][i], table[power - 1][mid + 1]);
            table[power][i] = val;
        }
        windowSize = windowSize << 1;
        power++;
    }

    for (int i = 0; i < q; i++)
    {
        // 3 2 4 5 1 1 5 3
        int start, end;
        cin >> start >> end; // 1 ~ x
        int length = (end - start + 1);
        int power = (int)log2(length);
        int powerOfTwoLength = pow(2, power);
        cout << min(table[power][start - 1], table[power][end - 1 - powerOfTwoLength + 1]) << "\n";
    }

    return 0;
}