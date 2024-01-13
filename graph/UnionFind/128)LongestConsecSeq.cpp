/**
 * Even tho it is not represented as a graph,
 * if we are grouping values, can think of union-find!
 */

class Solution
{
public:
    int getParent(unordered_map<int, int> &parent, int cur)
    {
        if (parent.count(cur) > 0 && parent[cur] == cur)
            return cur;
        return parent[cur] = getParent(parent, parent[cur]);
    }
    int longestConsecutive(vector<int> &nums)
    {
        unordered_map<int, int> parent;
        unordered_map<int, int> cnts;
        int ans = 0;
        // init map
        for (const auto &num : nums)
        {
            parent[num] = num;
        }
        // set parents with path compression
        for (const auto &num : nums)
        {
            if (parent.count(num - 1) > 0)
                parent[num] = getParent(parent, num - 1);
        }
        // count longest one
        for (const auto &[key, val] : parent)
        {
            ans = max(ans, ++cnts[getParent(parent, key)]);
        }
        return ans;
    }
};