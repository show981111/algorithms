/**
 * @brief LCA
 *
 * LCA is bascially a search function.
 * We need to find two nodes that we want!
 *
 *
 */
class Solution
{
public:
    TreeNode *findLCA(TreeNode *cur, TreeNode *p, TreeNode *q)
    {
        if (cur == nullptr)
            return nullptr;

        if (cur == p || cur == q)
            return cur;
        TreeNode *left = findLCA(cur->left, p, q);
        TreeNode *right = findLCA(cur->right, p, q);

        if (left && right)
            return cur; // found LCA
        else if (left)
            return left;
        else if (right)
            return right;
        else
            return nullptr;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        return findLCA(root, p, q);
    }
};