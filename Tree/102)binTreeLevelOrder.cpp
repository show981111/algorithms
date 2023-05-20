/**
 * @brief Level Order == BFS
 * BFS that considers depth!
 * -> think... nodes that are in the same level are popped together,
 * nodes that are in the next level are pushed together
 */

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        if (!root)
            return result;
        queue<TreeNode *> q;
        q.push(root);
        int depth = 0;

        while (!q.empty())
        {
            int levelSize = q.size();
            vector<int> level;
            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                level.push_back(cur->val);
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            result.push_back(level);
        }
        return result;
    }
};