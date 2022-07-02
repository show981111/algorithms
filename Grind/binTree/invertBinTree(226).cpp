class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;
        TreeNode *right = invertTree(root->left);
        TreeNode *left = invertTree(root->right);
        /**
         * We can't do
         * root->left = invertTree(root->right);
         * root->right = invertTree(root->left);
         * Because root->left is already inverted side
         *
         * Insetead we can use Swap function
         * if(root == nullptr)
                return nullptr;
            invertTree(root->left);
            invertTree(root->right);
            swap(root->left, root->right);
            return root;
         */
        root->left = left;
        root->right = right;
        return root;
    }
};