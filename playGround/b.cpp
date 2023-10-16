#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 *
 *
 */
void getPairs(unordered_map<int, vector<pair<int, int>>> &sumToPairs, unordered_map<int, int> &rCnt, int targetSum)
{
    unordered_map<int, int> mp;

    for (auto iter : rCnt)
    {
        if (mp.count(targetSum - iter.first) > 0)
        {
            sumToPairs[targetSum].push_back({iter.first, targetSum - iter.first});
        }
        mp[iter.first]++;
    }
}

bool sched(unordered_map<int, vector<pair<int, int>>> &sumToPairs, vector<int> &assign, unordered_map<int, int> &rCnt, vector<int> &diffs, int curIndex)
{
    if (curIndex >= assign.size())
    {
        // cout << "hi\n";
        return true;
    }

    bool res = false;
    for (auto &v : sumToPairs[diffs[curIndex - 1]])
    {
        int assignee = -1;
        if (v.first == assign[curIndex - 1])
        {
            assignee = v.second;
        }
        else if (v.second == assign[curIndex - 1])
        {
            assignee = v.first;
        }
        if (assignee != -1 && rCnt.count(assignee) > 0 && rCnt[assignee] > 0)
        {
            rCnt[assignee]--;
            assign[curIndex] = assignee;
            // cout << curIndex << " = " << assignee << endl;
            res = sched(sumToPairs, assign, rCnt, diffs, curIndex + 1);
            if (res)
                return true;
            rCnt[assignee]++;
            assign[curIndex] = 0;
        }
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> line(n, 0);
    vector<int> r(n, 0);
    unordered_map<int, int> rCnt;
    unordered_map<int, vector<pair<int, int>>> sumToPairs;
    vector<int> assign(n, 0);
    unordered_map<int, int> targetSums;
    vector<int> diffs;
    for (int i = 0; i < n; i++)
    {
        cin >> line[i];
        if (i > 0)
        {
            targetSums[line[i] - line[i - 1]]++;
            diffs.push_back(line[i] - line[i - 1]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cin >> r[i];
        rCnt[r[i]]++;
    }
    if (n == 1)
    {
        cout << r[0] << "\n";
        return 0;
    }

    for (auto iter : targetSums)
    {
        getPairs(sumToPairs, rCnt, iter.first);
    }

    for (auto iter : sumToPairs)
    {
        cout << iter.first << ": ";
        for (auto it : iter.second)
        {
            cout << it.first << "," << it.second << " ";
        }
    }
    cout << endl;
    for (auto i : diffs)
    {
        cout << i << " ";
    }
    cout << endl;
    for (auto iter : rCnt)
    {
        cout << iter.first << " : " << iter.second << endl;
    }

    for (auto &v : sumToPairs[diffs[0]])
    {
        assign[0] = v.first;
        rCnt[v.first]--;
        // cout << assign[0] << "GO!\n";
        bool res = sched(sumToPairs, assign, rCnt, diffs, 1);
        rCnt[v.first]++;
        if (res)
            break;
        assign[0] = v.second;
        rCnt[v.second]--;
        // cout << assign[0] << "GO!\n";
        res = sched(sumToPairs, assign, rCnt, diffs, 1);
        rCnt[v.second]++;
        if (res)
            break;
    }

    for (int i = 0; i < n; i++)
    {
        cout << assign[i] << " ";
    }

    return 0;
}