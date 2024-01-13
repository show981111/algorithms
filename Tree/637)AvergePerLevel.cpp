/**
 * Tree BFS!
 */
class Solution
{
public:
    vector<double> averageOfLevels(TreeNode *root)
    {
        vector<double> ans;
        if (root == nullptr)
            return ans;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int qSize = q.size();
            double sum = 0;
            for (int i = 0; i < qSize; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                sum += cur->val;
                if (cur->left != nullptr)
                    q.push(cur->left);
                if (cur->right != nullptr)
                    q.push(cur->right);
            }
            ans.push_back(sum / qSize);
        }
        return ans;
    }
};