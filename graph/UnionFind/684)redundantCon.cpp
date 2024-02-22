/**
 * Undirected graph cycle detection => Union-Find.
 *
 * Directed? -> DFS(3-coloring. Did i re-visit the node that is in the stack?)
 *              Bellman Ford (last iteration distance gets updated?)
 */

class Solution
{
public:
    // Find cycle and just remove one
    int getParent(vector<int> &parents, int node)
    {
        if (parents[node] == node)
            return node;
        else
            return parents[node] = getParent(parents, parents[node]);
    }
    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        vector<int> parents(edges.size() + 1); // 1-index
        for (int i = 1; i < parents.size(); i++)
            parents[i] = i;

        for (auto &e : edges)
        {
            int ap = getParent(parents, e[0]);
            int bp = getParent(parents, e[1]);

            if (ap < bp)
            {
                parents[bp] = ap; // merge
            }
            else if (bp < ap)
                parents[ap] = bp; //
            else
            {
                // cycle!
                return e;
            }
        }
        return vector<int>(); // nothing?
    }
};