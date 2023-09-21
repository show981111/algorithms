#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    cout << n << " " << m << endl;

    vector<int> pages(n, 0);
    vector<vector<int>> graph(n);
    vector<int> minCost(n, INT_MAX);
    vector<int> ind(n, 0);

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }
    for (int i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        ind[to - 1]++;
    }

    for (int i = 0; i < n; i++)
    {
        if (ind[i] == 0)
        {
            q.push(i);
            minCost[i] = pages[i];
        }
    }

    cout << "Hi";

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int child : graph[cur])
        {
            minCost[child] = min(minCost[child], minCost[cur] + pages[child]);
            ind[child]--;
            if (ind[child] == 0)
            {
                q.push(child);
            }
        }
    }
    for (int i = 0; i < minCost.size(); i++)
    {
        cout << minCost[i] << " ";
    }
    return 0;
}