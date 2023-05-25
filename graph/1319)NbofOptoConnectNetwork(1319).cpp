/**
 * @brief Union-Find
 * We can build a disjoint set using a union-find[Only For UnDirected Graph!]
 * Then we only need to find out how many edges do we need to connect each group
 * = number of groups - 1
 *
 * [Time complexity]
 * If we use path compression, find is O(a)
 * We call this function per each edge, so
 * O(E), then we traverse parr to get the number of groups, so O(V)
 * [Space complexity]
 * just for parr, O(V)
 */

class Solution
{
public:
    vector<int> parr;
    int getParent(int node)
    {
        if (node == parr[node])
            return node;
        else
            return parr[node] = getParent(parr[node]); // When getting a parent,
                                                       // we should get the parent of parent[node]
                                                       // then put it into parr[node]
    }

    int makeConnected(int n, vector<vector<int>> &connections)
    {
        if (connections.size() < n - 1)
            return -1;
        parr.resize(n);
        iota(parr.begin(), parr.end(), 0);
        for (auto &connection : connections)
        {
            int xp = getParent(connection[0]);
            int yp = getParent(connection[1]);
            parr[xp] = yp;
        }
        // should find the disconnected groups
        /*
        unordered_set<int> groups;
        for(auto i : parr){
            groups.insert(getParent(i));
        }
        int neededEdge = groups.size()-1;
        */
        int groups = 0;
        for (int i = 0; i < parr.size(); i++)
        {
            if (parr[i] == i) // if i == parr[i], that means i is the root of that group
                groups++;
        }
        return groups - 1;
    }
};

/**
 * @brief First attempt.
 * Didn't consider when the groups are disconnected
 * So, (1,2,3) (4,5,6) those groups are disconnected. but inside of each group
 * elements are connected
 */

class Solution
{
public:
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        vector<bool> connected(n);
        int totalEdge = connections.size();

        for (auto &connection : connections)
        {
            connected[connection[0]] = true;
            connected[connection[1]] = true;
        }
        int unConnnectedNum = 0;
        for (auto c : connected)
        {
            if (c == false)
                unConnnectedNum++;
        }
        if (totalEdge < n - 1)
            return -1;
        else
            return unConnnectedNum;
    }
};

// if there is a two connected group, we should connect those two groups!
//  but in this case, it will output 0

/**
 * @brief TLE DFS
 * TLE due to searching all the edges(connections),
 * not the Adj list
 *
 * DFS time complexity
 * O(V*(1+E/V)) => O(1+E/V) per every vertex.
 * When we are using a adj mat or list, getting all connected vertex are O(1+E/V)
 *
 * However, in this case, getting all vertices that is connected to each vertex is
 * O(E), so O(V*E) is the time complexity
 */

class Solution
{
public:
    vector<int> visited;
    void DFS(int start, vector<vector<int>> &connections)
    {
        visited[start] = true;
        for (auto con : connections)
        {
            if (con[0] == start)
            {
                if (visited[con[1]] == false)
                    DFS(con[1], connections);
            }
            else if (con[1] == start)
            {
                if (visited[con[0]] == false)
                    DFS(con[0], connections);
            }
        }
    }

    int makeConnected(int n, vector<vector<int>> &connections)
    {
        if (connections.size() < n - 1)
            return -1;
        visited.resize(n);
        int groups = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
                groups++;
                DFS(i, connections);
            }
        }
        return groups - 1;
    }
};

/**
 * @brief Successful DFS
 * [Time Complexity]
 * DFS(O(V+E)) + making adj list(O(E)), so O(V+E)
 *
 * [Space Complexity]
 * O(V+E) => it just means O(max(V, E)) we have V length array and max 2*E number of elements.
 * visited array(O(V)), adj list(O(V+E))
 */

class Solution
{
public:
    vector<int> visited;
    void DFS(int start, vector<vector<int>> &adj)
    {
        visited[start] = true;
        for (auto node : adj[start])
        {
            if (visited[node] == false)
                DFS(node, adj);
        }
    }

    int makeConnected(int n, vector<vector<int>> &connections)
    {
        if (connections.size() < n - 1)
            return -1;
        visited.resize(n, false);
        vector<vector<int>> adj(n);

        for (auto &con : connections)
        {
            adj[con[0]].push_back(con[1]);
            adj[con[1]].push_back(con[0]);
        } // create adj matrix

        // DFS, getting the number of groups(like number of islands)
        int groups = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
                groups++;
                DFS(i, adj);
            }
        }
        return groups - 1;
    }
};
