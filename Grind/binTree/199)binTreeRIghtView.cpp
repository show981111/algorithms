/**
 * @brief collect rightMost elements from each level of tree
 * BFS or DFS
 *
 * 1)BFS
 *  We can just collect the last element of Queue from each level
 * 2)DFS
 *  We can traverse right subtree first when we do DFS.
 *  Then, we can just collect the first element from each level!
 *  (first element we visit from each level)
 *  => We can think this as a reverse of preOrder (Root-> right -> left)
 */

// BFS
class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> ans;
        if (!root)
            return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int qSize = q.size();
            for (int i = 0; i < qSize; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
                if (i == qSize - 1)
                    ans.push_back(cur->val);
            }
        }
        return ans;
    }
};

// DFS
class Solution
{
public:
    void dfs(TreeNode *root, int level, vector<int> &ans)
    {
        if (!root)
            return;
        if (ans.size() == level)
            ans.push_back(root->val);
        dfs(root->right, level + 1, ans); // go to right subtree first!
        dfs(root->left, level + 1, ans);
    }
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> ans;
        dfs(root, 0, ans);

        return ans;
    }
};