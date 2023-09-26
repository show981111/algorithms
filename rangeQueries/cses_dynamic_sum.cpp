#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Dynamic Range Queries -> Binary Indexed Tree.
 *
 * Each cell is responsible for p(i) amount of contiguous cells.
 * p(i) = Least significant bit's position. EX) 12 = 1{100} so 100 = 4 cells
 *
 * (1) Get sum(1:k), only need to look up the number of 1's in the binary.
 * https://www.youtube.com/watch?v=RgITNht_f4Q&ab_channel=WilliamFiset
 * ex) 12 = 1100, so two 1's, so look up two cells to get all segments and perform sum.
 *     Specifically, [1:8](length 8 = 1000) + [9:12](length 4 = 100)
 * -> Number of 1's in binary is max logN cuz length of binary rep of N is logN.
 * Thus, sum takes O(logN)
 * => More formally, we keep removing LSB until the number becomes zero.
 * EX) 13 = 1101, so lookup 1 cell at 13-th index. Now, go to 1100 = 12 cell. will have 4 sums. now go 1000 = 8. Will have 8 sums.
 *
 * (2) Update I-th index to newVal.
 * https://www.youtube.com/watch?v=B-BkW9ZpKKM&ab_channel=WilliamFiset
 * Add LSB until it becomes larger than N. Since length of binary is max log(N),
 * update takes O(logN)
 * ex) update 13 = 1101. Add 1 since LSB is 0001.
 *         -> 14 = 1110. Add 2 since LSB is 0010.
 *         -> 16 = 1000. Add 8 since LSB is 1000.
 *         -> 24 out of bound.
 *
 * How to get LSB? = K & (-K)
 *
 */
typedef long long ll;
ll sum(int from, int to, vector<ll> &arr)
{ // get sum(arr[from:to])
    ll sum = 0;
    for (int i = from; i <= to; i++)
    {
        sum += arr[i];
    }
    return sum;
}
ll getPrefixSum(int k, vector<int> &p, vector<ll> &tree) // get sum from arr[1:k]
{
    ll res = 0;
    while (k >= 1)
    {
        res += tree[k];
        k -= p[k]; // could just do k & (-k)
    }
    return res;
}

void update(int k, ll newVal, vector<int> &p, vector<ll> &tree, vector<ll> &arr)
{
    ll offset = newVal - arr[k];
    arr[k] = newVal; // update val

    while (k <= arr.size() - 1)
    {
        tree[k] += offset;
        k += p[k];
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;

    vector<int> p(n + 1, 0); // 1-indexed binary tree
    vector<ll> tree(n + 1, 0);
    vector<ll> arr(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        p[i] = i & (-i);
    }

    for (int i = 1; i <= n; i++)
    {
        tree[i] = sum(i - p[i] + 1, i, arr);
    }

    for (int i = 0; i < q; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        { // Update
            update(b, c, p, tree, arr);
        }
        else if (a == 2)
        { // sum
            cout << getPrefixSum(c, p, tree) - getPrefixSum(b - 1, p, tree) << "\n";
        }
    }

    return 0;
}