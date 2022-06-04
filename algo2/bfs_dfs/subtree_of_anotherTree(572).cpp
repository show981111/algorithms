/**
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
    bool preOrder(TreeNode *org, TreeNode *subRoot)
    {
        if ((!org && subRoot) || (org && !subRoot))
            return false;
        if (!org && !subRoot)
            return true;
        if (org->val != subRoot->val)
            return false;
        return preOrder(org->left, subRoot->left) && preOrder(org->right, subRoot->right);
    }

    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (!root)
            return false;
        bool searchRes;
        if (root->val == subRoot->val)
        {
            searchRes = preOrder(root, subRoot);
            if (searchRes)
                return true;
        }
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};