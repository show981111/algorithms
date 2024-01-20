class Solution
{
public:
    /*
    Assigning a value to each variable based on equality => GROUPING!!!
    Grouping in a undirected graph -> UNION FIND

    Variables that are equal should be in the same group since they will be assigned the same value.
    Iterate variable pairs that are not equal, and if they are in the same group (have the same parent)
    then contradicton -> Return false
    */
    int getParent(unordered_map<int, int> &parents, int cur)
    {
        if (parents[cur] == cur)
            return cur;
        else
            return parents[cur] = getParent(parents, parents[cur]);
    }
    bool equationsPossible(vector<string> &equations)
    {
        vector<unordered_set<int>> uneq(30);
        unordered_map<int, int> parents;
        for (auto &eq : equations)
        {
            int a = eq[0] - 'a', b = eq.back() - 'a';
            if (parents.count(a) == 0)
                parents[a] = a;
            if (parents.count(b) == 0)
                parents[b] = b;
            if (eq.substr(1, 2) == "==")
            {
                if (uneq[a].count(b) > 0 || uneq[b].count(a) > 0)
                {
                    return false; // contradiction. a == b but a != b
                }
                int ap = getParent(parents, a);
                int bp = getParent(parents, b);
                if (ap < bp)
                {
                    parents[bp] = ap;
                }
                else if (ap > bp)
                    parents[ap] = bp;
            }
            else
            { // "!="
                uneq[a].insert(b);
                uneq[b].insert(a);
            }
        }

        // if they are unequal but has the same parent(same group), contradiction
        for (int i = 0; i < 30; i++)
        {
            for (int j : uneq[i])
            {
                if (getParent(parents, i) == getParent(parents, j))
                    return false;
            }
        }
        return true;
    }
};