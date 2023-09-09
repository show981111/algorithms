/**
 * From any node,
 * Diameter = sum of distances to 2 most farthest child
 *
 * For binary tree = depth of left child + depth of right child
 */

int getDiameter(TreeNode *root, int &ans)
{
    if (root == nullptr)
        return 0;

    int leftDepth = getDiameter(root->left, ans) + 1;
    int rightDepth = getDiameter(root->right, ans) + 1;
    // cout << leftDepth << " " << rightDepth << endl;
    ans = max(ans, leftDepth + rightDepth - 2);

    return max(leftDepth, rightDepth);
}
class Solution
{
public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        int ans = 0;
        getDiameter(root, ans);
        return ans;
    }
};

/**
 * For graph? Something like this
 */

class Solution
{
public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        queue<TreeNode *> q;

        q.push(root);
        vector<TreeNode *> level;
        while (!q.empty())
        {
            int qSize = q.size();
            level.clear();
            for (int i = 0; i < qSize; i++)
            {
                TreeNode *f = q.front();
                q.pop();
                level.push_back(f);
                if (f->left != nullptr)
                    q.push(f->left);
                if (f->right != nullptr)
                    q.push(f->right);
            }
        }
        for (auto node : level) // nodes at the last level of bfs -> the end of diameter.
        {
            cout << node->val << " ";
        }
        return getDistance(level.back()); // DFS call that get a distance to the farthest node
    }
};