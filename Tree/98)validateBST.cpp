/**
 * @brief BST
 *
 * Remember that ALL values in left subtree < cur < ALL values in right subtree!
 * Thus, we should keep track current Min and current max!
 *
 * Cur->value should be the MAX of left subtree, and MIN for right subtree
 *
 */

class Solution
{
public:
    bool helper(TreeNode *cur, TreeNode *curMin, TreeNode *curMax)
    {
        if (cur == nullptr)
            return true;
        // curNode should be the max value of leftSubtree
        bool left = helper(cur->left, curMin, cur);
        // curNode should be the min value of right subtree
        bool right = helper(cur->right, cur, curMax);
        bool judge = true;
        if (curMin != nullptr)
        {
            judge = judge && curMin->val < cur->val;
        }
        if (curMax != nullptr)
        {
            judge = judge && cur->val < curMax->val;
        }
        return left && right && judge;
    }

    bool isValidBST(TreeNode *root)
    {
        return helper(root, nullptr, nullptr);
    }
};

/**
 * @brief In order gives us ordered list!
 *
 * Prev should be update at each node, so we should use reference.
 * For parent, prev should be the RIGHTMOST node of the leftSubTree!!
 * Thus, prev should be updated when we are calling inOrder for leftSubtree.
 */

class Solution
{
public:
    bool inOrder(TreeNode *cur, optional<int> &prev)
    {
        if (cur == nullptr)
            return true;

        bool left = inOrder(cur->left, prev);
        bool ans = true;
        if (prev.has_value())
            ans = prev < cur->val;
        prev = cur->val;
        bool right = inOrder(cur->right, prev);
        return left && ans && right;
    }

    bool isValidBST(TreeNode *root)
    {
        optional<int> prev;
        return inOrder(root, prev);
    }
};