/**
 * @brief
 * Doing preOrder to merge tree from root node.
 * It should merge tree from root node. if its not, then it cannot differentiate
 * left or right child
 */
/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    TreeNode *mergeNode(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr && t2 == nullptr)
            return nullptr;
        if (t1 == nullptr)
            return t2;
        else if (t2 == nullptr)
            return t1;
        else
            return new TreeNode(t1->val + t2->val);
    }
    void mergeTreesHelper(TreeNode *&res, TreeNode *t1, TreeNode *t2)
    {
        res = mergeNode(t1, t2);
        if (res != nullptr)
        {
            TreeNode *t1_left = t1 == nullptr ? nullptr : t1->left;
            TreeNode *t1_right = t1 == nullptr ? nullptr : t1->right;
            TreeNode *t2_left = t2 == nullptr ? nullptr : t2->left;
            TreeNode *t2_right = t2 == nullptr ? nullptr : t2->right;

            mergeTreesHelper(res->left, t1_left, t2_left);
            mergeTreesHelper(res->right, t1_right, t2_right);
        }
    }
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
    {
        TreeNode *res;
        mergeTreesHelper(res, root1, root2);
        return res;
    }
};