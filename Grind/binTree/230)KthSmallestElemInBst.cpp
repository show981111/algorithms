/**
 * @brief Sorting BST => INorder Traversal!
 *
 * Recording recursive process from 3rd perspective.
 * Add parameter and pass it by reference!
 */

class Solution
{
public:
    void kthSmallestHelper(TreeNode *root, int &k, int &index, int &ans)
    {
        if (root == nullptr)
        {
            return;
        }
        kthSmallestHelper(root->left, k, index, ans);
        if (index == k)
        {
            ans = root->val;
            k = -1; // found the answer, reset k and return
            return;
        }
        index++;
        kthSmallestHelper(root->right, k, index, ans);
    }
    int kthSmallest(TreeNode *root, int k)
    {
        int ans = -1;
        int index = 1;
        kthSmallestHelper(root, k, index, ans);
        return ans;
    }
};