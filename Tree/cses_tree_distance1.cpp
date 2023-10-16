#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * https://cses.fi/problemset/task/1132/
 * Get the length to the farthest node from each node.
 *
 * I know how to do it from one noce.. but how to do this in each node?
 *
 * Think from arbitrary node X.
 * (1) Go through parent: 1 + maxLength(parent)
 *      - One thing to note is, maxLength from parent can go through X since X is the child of parent.
 *          => this is why we have to store top two length
 * (2) Pick farthest descendant
 *
 * Ok, we got the algorithm but how can we calculate both at the same time?
 * We get the length to the farthest descendant while returning from the children,
 * but we have to compute maxLength before we do dfs on children cuz child has to use this value.
 *
 * -> Split into two dfs!
 * First dfs) Bottom up, record the farthest desecendant.
 * Second dfs) Top down, compute maxLength for parent and pass to children.
 */

struct Dist
{
    int nextNode = -1;
    int length = 0;
};

struct Record
{
    Dist first;
    Dist second;
};

int getDistanceToLeaf(int cur, int par, vector<vector<int>> &tree, vector<Record> &toLeaf)
{
    Dist firstDist;
    Dist secondDist;

    for (int child : tree[cur])
    {
        if (child == par)
            continue;
        int childDist = getDistanceToLeaf(child, cur, tree, toLeaf) + 1;
        if (childDist > firstDist.length)
        {
            secondDist = firstDist;
            firstDist.length = childDist;
            firstDist.nextNode = child;
        }
        else if (childDist > secondDist.length)
        {
            secondDist.length = childDist;
            secondDist.nextNode = child;
        }
    }

    toLeaf[cur] = {firstDist, secondDist};

    if (firstDist.length == 0)
    { // leaf
        return 0;
    }

    return firstDist.length;
}

void getMaxLength(int cur, int par, vector<vector<int>> &tree, vector<Record> &toLeaf, vector<Record> &maxLength)
{
    vector<Dist> temp;
    Dist maxFromParent = {par, 0};
    if (par != -1)
    {
        maxFromParent.length = maxLength[par].first.length + 1;
        if (maxLength[par].first.nextNode == cur) // if the max path goes through current child, choose next one.
        {
            maxFromParent.length = maxLength[par].second.length + 1;
        }
    }
    temp.push_back(maxFromParent);
    temp.push_back(toLeaf[cur].first);
    temp.push_back(toLeaf[cur].second);
    sort(temp.begin(), temp.end(), [](const Dist &a, const Dist &b)
         { return a.length > b.length; });
    maxLength[cur].first = temp[0];
    maxLength[cur].second = temp[1];

    for (int child : tree[cur])
    {
        if (child == par)
            continue;
        getMaxLength(child, cur, tree, toLeaf, maxLength);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<vector<int>> tree(n + 1);
    for (int i = 1; i <= n - 1; i++)
    {
        int from, to;
        cin >> from >> to;
        tree[from].push_back(to);
        tree[to].push_back(from);
    }
    vector<Record> toLeaf(n + 1);
    vector<Record> maxLength(n + 1);

    getDistanceToLeaf(1, -1, tree, toLeaf);
    getMaxLength(1, -1, tree, toLeaf, maxLength);

    for (int i = 1; i <= n; i++)
    {
        cout << maxLength[i].first.length << " ";
    }
    cout << "\n";
    return 0;
}