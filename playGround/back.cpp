#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

bool check(map<int, set<int>> &rooks,
           vector<bool> &rowcheck,
           vector<bool> &colCheck, int r1, int c1, int r2, int c2)
{
    auto rowFrom = rooks.lower_bound(r1);
    auto rowTo = rooks.upper_bound(r2);

    for (auto iter = rowFrom; iter != rowTo; ++iter)
    {
        cout << "ROW " << iter->first << endl;
        auto fromCol = iter->second.lower_bound(c1);
        auto toCol = iter->second.upper_bound(c2);
        for (auto colIter = fromCol; colIter != toCol; ++colIter)
        {
            if (rowcheck[iter->first] || colCheck[*colIter])
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;

    map<int, set<int>> rooks; // row -> cols
    vector<bool> rowcheck(n + 1, false);
    vector<bool> colCheck(n + 1, false);

    for (int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int r, c;
            cin >> r >> c;
            rowcheck[r] = true;
            colCheck[c] = true;
            rooks[r].insert(c);
        }
        else if (t == 2)
        {
            int r, c;
            cin >> r >> c;
            rowcheck[r] = false;
            colCheck[c] = false;
            rooks[r].erase(c);
            if (rooks[r].size() == 0)
            {
                rooks.erase(r);
            }
        }
        else if (t == 3)
        {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            bool res = check(rooks, rowcheck, colCheck, r1, c1, r2, c2);
            if (res)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}