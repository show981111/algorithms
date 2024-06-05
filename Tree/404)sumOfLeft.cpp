class Solution
{
public:
    int helper(TreeNode *cur, bool fromLeft)
    {
        if (cur == nullptr)
            return 0;
        if (cur->left == nullptr && cur->right == nullptr && fromLeft)
        {
            return cur->val;
        }
        return helper(cur->left, true) + helper(cur->right, false);
    }
    int sumOfLeftLeaves(TreeNode *root)
    {
        return helper(root, false);
    }
};