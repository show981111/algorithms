class Solution
{
public:
    bool helper(TreeNode *l, TreeNode *r)
    {
        if (l == nullptr && r == nullptr)
        {
            return true;
        }
        else if (l == nullptr || r == nullptr)
        {
            return false;
        }
        else
        {
            if (l->val != r->val)
                return false;
            else
            {
                return helper(l->left, r->right) && helper(l->right, r->left);
            }
        }
    }
    bool isSymmetric(TreeNode *root)
    {
        return helper(root->left, root->right);
    }
};