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
    bool isCompleteTree(TreeNode *root)
    {
        if (!root)
            return true;
        queue<TreeNode *> q;
        q.push(root);
        bool isEmpty = false;

        while (!q.empty())
        {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                if (cur != nullptr && isEmpty)
                {
                    return false;
                }
                else if (cur == nullptr)
                {
                    isEmpty = true;
                    continue;
                }

                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return true;
    }
};