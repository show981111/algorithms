class Solution
{
public:
    /*
    Need to find the critical path from the head.
    Using DFS, track the maximum inform time path!
    */
    void dfs(int cur, int curTime, vector<vector<int>> &tree, vector<int> &informTime,
             int &longestInformTime)
    {
        if (tree[cur].size() == 0)
        {
            longestInformTime = max(longestInformTime, curTime);
            return;
        }

        for (int child : tree[cur])
        {
            dfs(child, curTime + informTime[cur], tree, informTime, longestInformTime);
        }
    }
    int numOfMinutes(int n, int headID, vector<int> &manager, vector<int> &informTime)
    {
        vector<vector<int>> tree(n);
        for (int i = 0; i < n; i++)
        {
            if (manager[i] != -1)
                tree[manager[i]].push_back(i); // i's manager is manager[i]
        }
        int longestInformTime = 0;
        dfs(headID, 0, tree, informTime, longestInformTime);
        return longestInformTime;
    }
};

/**
 * Using BFS but climbing up from the leaf
 * Need a dijkstra like cost table to avoid redundant pushing to the queue of node
 */
int numOfMinutes(int n, int headID, vector<int> &manager, vector<int> &informTime)
{
    /*
    Using BFS, starting from the leaf, we can climb up to head using manager(parent) array
    */
    queue<int> q;
    vector<int> maxTime(n, 0); // record the maximum time to reach the node
    for (int i = 0; i < n; i++)
    {
        if (informTime[i] == 0)
        { // i has no child if informTime[i] == 0 (based on constraints)
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int f = q.front();
        q.pop();

        if (manager[f] != -1)
        {
            int m = manager[f];
            if (maxTime[m] < maxTime[f] + informTime[m])
            {
                // if we found a path that exceeds the current max time to reach N, push to the queue and re-traverse
                // Still, we cannot stop it from recomputing the cost from m ~ head
                maxTime[m] = max(maxTime[m], maxTime[f] + informTime[m]);
                q.push(m);
            }
        }
    }
    return maxTime[headID];
}