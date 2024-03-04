/**
 * Using BFS to do level traversal left->right!
 */
class Solution
{
public:
    bool isEvenOddTree(TreeNode *root)
    {
        queue<TreeNode *> q;
        q.push(root);
        int level = 0;
        while (!q.empty())
        {
            int qSize = q.size();
            int prev = 0;
            for (int i = 0; i < qSize; i++)
            {
                TreeNode *f = q.front();
                if (level % 2 == 0)
                {
                    if (f->val % 2 == 0)
                        return false;
                    if (prev != 0 && prev >= f->val)
                        return false;
                }
                if (level % 2 == 1)
                {
                    if (f->val % 2 == 1)
                        return false;
                    if (prev != 0 && prev <= f->val)
                        return false;
                }
                prev = f->val;
                q.pop();

                if (f->left)
                    q.push(f->left);
                if (f->right)
                    q.push(f->right);
            }
            level++;
        }
        return true;
    }
};