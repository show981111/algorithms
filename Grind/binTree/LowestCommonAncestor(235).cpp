/**
 * @brief If it is not a BST,
 * We should find the root of subTree where both p and q eixsts!
 *
 */
class Solution
{
public:
    TreeNode *LcaHelper(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr)
            return nullptr;
        if (root == p)
            return root;
        if (root == q)
            return root;
        TreeNode *left = LcaHelper(root->left, p, q);
        TreeNode *right = LcaHelper(root->right, p, q);
        if (left != nullptr && right != nullptr) // if both are not nullptr, it means
            return root;                         // the subtree of this root contains both p and q
        else if (left == nullptr)                // if left is null, then we only found right so return right
            return right;
        else if (right == nullptr) // if right is null, we've only found the left
            return left;           // return what we found
        else
            return nullptr; // we couldn't find anyting
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        return LcaHelper(root, p, q);
    }
};

/**
 * @brief Using that this is a BST
 * LCA for BST is the first(Highest) element such that
 * samller val < root val < bigger val
 * if we go above that root, then the value becomes bigger or smaller than both elements!
 */

class Solution
{
public:
    TreeNode *LcaHelper(TreeNode *root, TreeNode *left, TreeNode *right)
    {
        if (root->val < left->val)
            return LcaHelper(root->right, left, right);
        else if (root->val > right->val)
            return LcaHelper(root->left, left, right);
        return root;
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (p->val > q->val)
            return LcaHelper(root, q, p);
        else
            return LcaHelper(root, p, q);
    }
};