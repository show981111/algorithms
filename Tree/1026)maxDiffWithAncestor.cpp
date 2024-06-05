/**
 * Need to find the biggest different between ancestor and child.
 * Brute-force: O(N^2) -> Compare the child with all ancestor.
 *
 * Is it necessary to compare with all ancestors?
 * What we need is, min and max in root ~ leaf. Then max diff is just max - min
 * Ok so we only need to track min and max!
 * 1) ordered map: push the value as we travel pre-order. Pop it after we are done.
 *      O(NlogN)
 * 2) Do we need a map? previous min and max can be passed as a parameter.
 *      After traversal is done, we can just return so that the previous call can use its own
 *      min and max!
 *      O(N)
 */
class Solution
{
public:
    void helper(TreeNode *cur, map<int, int> &mp, int &maxDiff)
    {
        if (cur == nullptr)
            return;

        mp[cur->val]++;
        maxDiff = max(maxDiff, abs((mp.begin()->first) - (mp.rbegin()->first)));
        helper(cur->left, mp, maxDiff);
        helper(cur->right, mp, maxDiff);
        if (mp[cur->val] == 1)
            mp.erase(cur->val);
    }
    int maxAncestorDiff(TreeNode *root)
    {
        int ans = 0;
        map<int, int> mp;
        helper(root, mp, ans);
        return ans;
    }
};

/**
 * Alternative: O(N)
 * No map.
 */
class Solution
{
public:
    void helper(TreeNode *cur, int minVal, int maxVal, int &maxDiff)
    {
        if (cur == nullptr)
            return;
        int newMin = min(minVal, cur->val);
        int newMax = max(maxVal, cur->val);
        maxDiff = max(maxDiff, newMax - newMin);
        helper(cur->left, newMin, newMax, maxDiff);
        helper(cur->right, newMin, newMax, maxDiff);
    }
    int maxAncestorDiff(TreeNode *root)
    {
        const int MAX = 5001, MIN = 0;
        int ans = 0;
        helper(root, MAX, MIN, ans);
        return ans;
    }
};
