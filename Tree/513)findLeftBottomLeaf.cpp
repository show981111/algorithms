/**
 * @brief
 * Recursive with Tree
 *
 * 1. What should we return?
 * 2. What should we pass?
 * 3. How should we join the result?
 * 4. Base Case?
 *
 * Another way to solve this is BFS
 * but, do BFS from Right -> left
 * Then just retun the node which is popped lastly!
 *
 */

class Solution
{
public:
    struct Info
    {
        TreeNode *node;
        int depth;
        Info(TreeNode *n, int d) : node(n), depth(d) {}
    };
    Info helper(TreeNode *root)
    {
        if (root == nullptr)
            return Info(root, 0);

        Info left = helper(root->left);
        Info right = helper(root->right);

        if (left.node != nullptr && right.node != nullptr)
        {
            if (left.depth >= right.depth)
            {
                return Info(left.node, left.depth + 1);
            }
            else
            { // if(right.depth > left.depth)
                return Info(right.node, right.depth + 1);
            }
        }
        else if (left.node != nullptr)
        {
            return Info(left.node, left.depth + 1);
        }
        else if (right.node != nullptr)
        {
            return Info(right.node, right.depth + 1);
        }
        else
        {
            return Info(root, 0);
        }
    }
    int findBottomLeftValue(TreeNode *root)
    {
        return helper(root).node->val;
    }
};

/**
 * Simple in-order traversal
 * If we always go to left first, for that depth, we will go to the leftmost element first
 *
 * So, for that depth, the first node we visit will be the leftmost node from that depth!
 */

class Solution
{
public:
    void helper(TreeNode *cur, int curDepth, TreeNode *&ans, int &depth)
    {
        if (cur == nullptr)
            return;
        if (curDepth > depth)
        {
            ans = cur;
            depth = curDepth;
        }
        helper(cur->left, curDepth + 1, ans, depth);
        helper(cur->right, curDepth + 1, ans, depth);
    }
    int findBottomLeftValue(TreeNode *root)
    {
        TreeNode *ans = nullptr;
        int depth = -1;

        helper(root, 0, ans, depth);
        return ans->val;
    }
};