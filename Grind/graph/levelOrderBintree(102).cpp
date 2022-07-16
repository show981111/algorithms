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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> q;
        vector<vector<int>> res;

        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            vector<int> level;
            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                if (cur == nullptr)
                    continue;

                level.push_back(cur->val);
                q.push(cur->left);
                q.push(cur->right);
            }
            if (!level.empty())
                res.push_back(level);
        }
        return res;
    }
};