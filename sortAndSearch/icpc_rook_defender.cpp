#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

/**
 * https://codeforces.com/group/62c8bIEN9G/contest/474705/problem/E
 *
 * Subrectangle is attacked if all cells are attacked by at least one row.
 *
 * First way)
 * Using colCheck, rowCheck vector<bool> array, just iterate from r1 ~ r2, c1~c2 and see if
 * there is a rook in all rows or all cols.
 * => O(q*(max(r2-r1, c2-c1))) linear in terms of rectangle.
 *
 * Second way.
 * Think that rook should be at all rows or all cols of rectangle.
 * This is the reason why I need to linearly search all rows and cols.
 * How about, I check this by free cols and free rows?
 * If there is one free row between r1 and r2, row is not attacked.
 * If there is one free col between c1 and c2, col is not attacked.
 * => Using this, do bin search on free rows and free cols!
 */

bool check(set<int> &freeRows,
           set<int> &freeCols, int r1, int c1, int r2, int c2)
{
    bool rowRes = true;
    auto rowBegin = freeRows.lower_bound(r1);          // find the first elem, that is at least r1. (r1 <= elem)
    if (rowBegin != freeRows.end() && *rowBegin <= r2) // if that is smaller than r2, then there is one free row in between!
    {
        rowRes = false;
    }

    bool colRes = true;
    auto colBegin = freeCols.lower_bound(c1); // Same here
    if (colBegin != freeCols.end() && *colBegin <= c2)
    {
        colRes = false;
    }
    return rowRes || colRes;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;

    // vector<vector<char>> board(n + 1, vector<char>(n + 1, '-'));
    unordered_map<int, int> rowCnt;
    unordered_map<int, int> colCnt;
    set<int> freeRows;
    set<int> freeCols;
    for (int i = 1; i <= n; i++)
    {
        freeRows.insert(i);
        freeCols.insert(i);
    }

    for (int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int r, c;
            cin >> r >> c;
            rowCnt[r]++;
            colCnt[c]++;

            freeRows.erase(r);
            freeCols.erase(c);
            // board[r][c] = 'R';
        }
        else if (t == 2)
        {
            int r, c;
            cin >> r >> c;
            rowCnt[r]--;
            colCnt[c]--;
            if (rowCnt[r] == 0)
            {
                rowCnt.erase(r);
                freeRows.insert(r);
            }
            if (colCnt[c] == 0)
            {
                colCnt.erase(c);
                freeCols.insert(c);
            }
            // board[r][c] = '-';
        }
        else if (t == 3)
        {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            bool res = check(freeRows, freeCols, r1, c1, r2, c2);
            if (res)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }

    return 0;
}