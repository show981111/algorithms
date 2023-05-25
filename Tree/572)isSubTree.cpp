/**
 * @brief Compare Tree
 *
 * Pre/Post order is unique for each tree.
 *
 * TC: O(R * S) (R is the size of root, S is the size of subRoot)
 *  => need to check "isSame" at each node that has the same value!
 *
 * Otherwise, we should serialize(pre, or post order) and use KMP or something
 *
 */
class Solution
{
public:
    bool isSame(TreeNode *root, TreeNode *subRoot)
    {
        if ((root == nullptr && subRoot != nullptr) ||
            (root != nullptr && subRoot == nullptr))
            return false;
        else if (root == nullptr && subRoot == nullptr)
            return true;

        if (root->val == subRoot->val)
            return isSame(root->left, subRoot->left) && isSame(root->right, subRoot->right);
        else
            return false;
    }

    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if ((root == nullptr && subRoot != nullptr) ||
            (root != nullptr && subRoot == nullptr))
            return false;
        else if (root == nullptr && subRoot == nullptr)
            return true;
        // both root and subroot is not null
        if (root->val == subRoot->val)
        {
            bool isCurSubtree = isSame(root, subRoot);
            if (isCurSubtree)
                return true;
        }

        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};