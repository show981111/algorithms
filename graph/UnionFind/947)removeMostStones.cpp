class Solution
{
public:
    /*
    Observation:
    1. if it is connected(share row or col), then at least one can be removed.
    2. Within the Connected component, we can remove all but one.
        - Worst case is that they are connected with only one edge -> still can remove all but one
        - Based on Top-sort order, it is impossible to make two nodes both indegree zeros in the connected components (If indegree == 0, cannot remove)

    => Now problem is, how many groups are there?
    1. Need to create an edge among stones that are sharing row & cols
        - Creating an edge.. O(V^2) cuz we need to consider all pairs
        - Use MAP. Save current node's row and col, O(1) look-up for checking if it shares row/col.
          Then, unify current node that node which has the same row/col

    2. Counting #unique parents in Union-find array
    */
    typedef int Node;
    Node getParent(Node a, vector<Node> &p)
    {
        if (p[a] == a)
            return a;
        else
            return p[a] = getParent(p[a], p); // path compression
    }
    void unify(Node a, Node b, vector<Node> &p)
    { // Merge PARENT! = connect parent's parent
        Node aParent = getParent(a, p);
        Node bParent = getParent(b, p);
        if (aParent < bParent)
        {
            p[bParent] = aParent; // Should Fix the parent of bParent not just p[b]
            // Why? since b & bParent are connected, it needs to connect aParent with bParent
            // so that all components connected to bParents are also connected to aParent.
        }
        else if (aParent > bParent)
        {
            p[aParent] = bParent;
        }
    }
    int removeStones(vector<vector<int>> &stones)
    {
        vector<Node> parents(stones.size());
        for (int i = 0; i < stones.size(); i++)
            parents[i] = i;
        unordered_map<int, int> rowToNode; // row -> Node id
        unordered_map<int, int> colToNode; // col -> Node id

        for (int i = 0; i < stones.size(); i++)
        {
            int rowNum = stones[i][0];
            int colNum = stones[i][1];
            if (rowToNode.count(rowNum) > 0)
            {
                unify(i, rowToNode[rowNum], parents);
            }
            else
            {
                rowToNode[rowNum] = i;
            }
            if (colToNode.count(colNum) > 0)
            {
                unify(i, colToNode[colNum], parents);
            }
            else
            {
                colToNode[colNum] = i;
            }
        }
        unordered_set<Node> groups;
        for (Node v : parents)
        {
            groups.insert(getParent(v, parents));
        }
        return stones.size() - groups.size();
    }
};