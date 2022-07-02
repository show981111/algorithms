/**
 * @brief Calculating height and difference at the same time
 * just put the "ans(boolean value)" as a parameter to see its unbalanced or not
 * Then just insert the code that calculate the diff and decide isUnbalanced
 * into the getting Height code!
 */
class Solution
{
public:
    int isBalancedHelper(TreeNode *root, bool &ans)
    {
        if (root == nullptr)
            return 0;
        int l = isBalancedHelper(root->left, ans);
        int r = isBalancedHelper(root->right, ans);
        int diff = l - r;
        if (diff < -1 || diff > 1)
            ans = false;
        return max(l, r) + 1;
    }
    bool isBalanced(TreeNode *root)
    {
        bool ans = true;
        int res = isBalancedHelper(root, ans);
        return ans;
    }
};

/**
 * @brief Caculating the height of children node everytime
 * to get difference
 *
 * Time : O(N^2) (at each node, we call getHeight...)
 * Space : O(N)
 */
class Solution
{
public:
    int getHeight(TreeNode *start)
    {
        if (start == nullptr)
            return 0;
        return max(getHeight(start->left), getHeight(start->right)) + 1;
    }
    bool isBalancedHelper(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        int diff = getHeight(root->left) - getHeight(root->right);
        if (diff > 1 || diff < -1)
            return false;
        else
        {
            return isBalancedHelper(root->left) && isBalancedHelper(root->right);
        };
    }
    bool isBalanced(TreeNode *root)
    {
        return isBalancedHelper(root);
    }
};