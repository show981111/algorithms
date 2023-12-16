class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;
        TreeNode *invertedRight = invertTree(root->right);
        TreeNode *invertedLeft = invertTree(root->left);
        root->left = invertedRight; // invert subtree
        root->right = invertedLeft;
        return root;
    }
};