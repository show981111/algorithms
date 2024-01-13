/**
 * relationship between variables
 * ex) a = 2b, b = 3c
 * -> Since it is a relationship, can be represented as a graph!
 *
 * Finding a relationship is a simple DFS from source to target
 */

class Solution
{
public:
    /*
    a / b = 2, b / c = 3
    a -> b -> 2
    b -> a -> 1/2
      -> c -> 3
    c -> b -> 1/3

    a / c?
    a - (2) -> b - (3) -> c
    a = 2b = 6c
    */
    struct To
    {
        string dest;
        double val;
    };
    double dfs(unordered_map<string, vector<To>> &rel, unordered_set<string> &vis, string &cur, string &dest, double curVal)
    {
        if (cur == dest)
            return curVal;

        for (auto &neighbor : rel[cur])
        {
            if (vis.count(neighbor.dest) > 0)
                continue;

            if (neighbor.dest == dest)
            {
                return curVal * neighbor.val;
            }
            vis.insert(neighbor.dest);
            double res = dfs(rel, vis, neighbor.dest, dest, curVal * neighbor.val);
            if (res > -1)
                return res;
        }

        return -1;
    }
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        unordered_map<string, vector<To>> rel;

        for (int i = 0; i < equations.size(); i++)
        {
            rel[equations[i][0]].push_back({equations[i][1], values[i]});
            rel[equations[i][1]].push_back({equations[i][0], 1 / values[i]});
        }
        vector<double> ans;
        for (auto &q : queries)
        {
            unordered_set<string> vis;

            if (rel.count(q[0]) == 0 || rel.count(q[1]) == 0)
            {
                ans.push_back(-1);
                continue;
            }
            vis.insert(q[0]);
            double res = dfs(rel, vis, q[0], q[1], 1);
            ans.push_back(res);
        }
        return ans;
    }
};