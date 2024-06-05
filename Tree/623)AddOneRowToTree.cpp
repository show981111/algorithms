/**
 * Recursive function.
 * What do I need?
 * We can propagate information from top->down by passing it as a parameter.
 * We can collect information from bottom->top by returning the value.
 */
class Solution
{
public:
    TreeNode *helper(TreeNode *cur, int curDepth, int dir, const int targetDepth, const int val)
    {
        if (targetDepth == 0 || (cur == nullptr && targetDepth == curDepth))
        {
            TreeNode *t = new TreeNode(val, cur, nullptr);
            return t;
        }
        if (cur == nullptr)
            return nullptr;
        if (curDepth > targetDepth)
            return cur;
        TreeNode *l = helper(cur->left, curDepth + 1, -1, targetDepth, val);
        TreeNode *r = helper(cur->right, curDepth + 1, 1, targetDepth, val);
        if (curDepth == targetDepth - 1)
        {
            cur->left = l;
            cur->right = r;
        }
        else if (curDepth == targetDepth)
        {
            TreeNode *t = new TreeNode(val);
            if (dir == 1)
            {
                t->right = cur;
            }
            else
            {
                t->left = cur;
            }
            cur = t;
        }
        return cur;
    }
    TreeNode *addOneRow(TreeNode *root, int val, int depth)
    {
        return helper(root, 0, 0, depth - 1, val);
    }
};