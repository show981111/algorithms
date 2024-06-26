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
    bool isSameTreeHelper(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr && q == nullptr)
            return true;
        else if (p != nullptr && q != nullptr)
        {
            return p->val == q->val && isSameTreeHelper(p->left, q->left) && isSameTreeHelper(p->right, q->right);
        }
        else
            return false; // only one of them are nullptr
    }
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        return isSameTreeHelper(p, q);
    }
};