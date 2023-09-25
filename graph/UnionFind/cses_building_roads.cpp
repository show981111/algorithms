#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

/**
 * https://cses.fi/problemset/task/1666/
 * Union Find -> Undirected graph connectivity.
 *
 * If I do Path compression it will be O(a(n)) -> Almost constant
 * Without path compression, if we merge smaller one to the bigger one, O(logN) (hight of the graph)
 *
 */

int getParent(vector<int> &parent, int cur)
{
    if (parent[cur] == cur)
        return cur;

    return parent[cur] = getParent(parent, parent[cur]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int cities, roads;

    cin >> cities >> roads;
    vector<int> parent(cities + 1);
    for (int i = 1; i < parent.size(); i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < roads; i++)
    {
        int x, y;
        cin >> x >> y;

        if (x < y)
        {
            parent[getParent(parent, y)] = getParent(parent, x);
        }
        else
        {
            parent[getParent(parent, x)] = getParent(parent, y);
        }
    }
    unordered_set<int> roots;
    for (int i = 1; i <= cities; i++)
    {
        roots.insert(getParent(parent, i));
    }

    cout << roots.size() - 1 << "\n";
    if (roots.size() >= 2)
    {
        auto b = roots.begin();
        for (auto iter = next(b, 1); iter != roots.end(); ++iter)
        {
            cout << *b << " " << *iter << "\n";
        }
    }

    return 0;
}