/**
 * @brief Using Height!
 * Why not passing height as a reference?
 *  Height is not getting updated globally...
 *  We need to take the max of left and right.
 *  This result should not affect the other sibling nodes(nodes in the same level)
 * On the other hand, ans should be updated globally. We judge "ans" at each node and
 * if it is false for only one node, then the overall result is false!
 *
 * Remember, for balance, height matters, not depth. Depth is just parent + 1!
 *
 * TC: O(n), ans is updated at each node.
 * We are calculating height only once at each node using the result from children!
 * => not O(N^2)
 *
 */

class Solution
{
public:
    int helper(TreeNode *cur, bool &ans)
    {
        if (cur == nullptr || !ans)
            return 0;
        int leftHeight = helper(cur->left, ans);
        int rightHeight = helper(cur->right, ans);

        ans = ans && abs(leftHeight - rightHeight) <= 1;
        return max(leftHeight, rightHeight) + 1;
    }
    bool isBalanced(TreeNode *root)
    {
        bool ans = true;
        helper(root, ans);
        return ans;
    }
};