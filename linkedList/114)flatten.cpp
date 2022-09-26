/**
 * @brief Recursive call technic..
 * if we need the result of the next call? -> use return.
 * if we need the result of the previous call? -> pass by ref
 *
 */

class Solution
{
public:
    void helper(TreeNode *cur, TreeNode *&prev)
    {
        if (cur == nullptr)
            return;
        TreeNode *l = cur->left;
        TreeNode *r = cur->right;
        if (prev != nullptr)
        {
            prev->left = nullptr;
            prev->right = cur;
        }
        prev = cur;
        helper(l, prev);
        helper(r, prev);
    }
    void flatten(TreeNode *root)
    {
        TreeNode *prev = nullptr;
        return helper(root, prev);
    }
};