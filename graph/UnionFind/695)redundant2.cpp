/*
Union Find in Directed graph?
=> To find a redundant path! a -> b -> c, a -> c

Every node has exactly one parent other than a root.

1) So if there is a node with two parents? one edge should be removed.
-> Could be a cycle OR redundant path. EX) a -> b -> c, a -> c (no cycle but redundant path)
-> If there is a cycle, delete the one that is causing the cycle. Otherwise delete either.

2) If all nodes have one indegree
-> 100% cycle. Why? since there is a no root. (root will have 0 indegree)
-> Delete the edge that is causing the cycle.
*/
class Solution
{
public:
    int getParent(vector<int> &p, int cur)
    {
        if (p[cur] == cur)
            return cur;
        else
            return p[cur] = getParent(p, p[cur]);
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges)
    {
        vector<int> p(edges.size() + 1);
        vector<int> prev(edges.size() + 1);
        for (int i = 1; i <= edges.size(); i++)
        {
            p[i] = i;
        }
        vector<int> ind(edges.size() + 1, 0);
        vector<int> cand;
        for (const auto &e : edges)
        {
            ind[e[1]]++;
            if (ind[e[1]] > 1)
            {
                // erase e or {p[e[1]].parent, e[1]}
                // cout << e[0] << " " << e[1] << endl;
                cand = e;
                break;
            }
            prev[e[1]] = e[0];
        }

        // indegree is all one. -> CYCLE EXISTS
        for (const auto &e : edges)
        {
            if (cand == e)
                continue;

            int ap = getParent(p, e[0]);
            int bp = getParent(p, e[1]);
            if (ap == bp)
            {
                if (cand.size() == 2)
                {
                    return {prev[cand[1]], cand[1]};
                }
                return e;
            }
            else if (ap < bp)
            {
                p[bp] = ap;
            }
            else
            {
                p[ap] = bp;
            }
        }
        if (cand.size() == 2)
            return cand; // later one

        return {};
    }
};
