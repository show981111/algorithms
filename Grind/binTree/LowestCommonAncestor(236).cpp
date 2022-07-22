/**
 * @brief Recursive on Binary tree
 * Break Condition(root == nullptr)
 * Traverse to Left and Right
 * Get back from the traverse, do something with the return value
 */
class Solution
{
public:
    TreeNode *getLCA(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr)
            return nullptr;
        if (root == p || root == q)
            return root;
        TreeNode *l = getLCA(root->left, p, q);
        TreeNode *r = getLCA(root->right, p, q);
        if (l != nullptr && r != nullptr)
            return root;
        else if (l)
            return l;
        else if (r)
            return r;
        return nullptr;
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        return getLCA(root, p, q);
    }
};