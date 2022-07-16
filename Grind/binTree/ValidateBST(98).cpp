/**
 * @brief BST
 * Simply comparing left < root < right does not solve the problem
 * EX)
 *      5
 *  3       8
 *        4    9
 * This is invalid BST, but if we compare just left, root, right of each node,
 * it will return valid.
 *
 * Thus, we should use InOrder traverse to serialize the BST!
 * In each recursive step, we can compare current node with previous node.
 * Then if it is not sorted, NOT BST!
 */

class Solution
{
public:
    bool inOrder(TreeNode *root, optional<int> &prev)
    {
        bool res = true;
        if (root->left)
        {
            res = inOrder(root->left, prev);
            if (!res)
                return false;
        }
        if (prev.has_value() && prev >= root->val)
            return false;

        prev = root->val; // set prev to current val.
        // we should set value at this stage, other than that, we compare a wrong value.
        // Since it is InOrder, value should be change at here!!!!!

        if (root->right)
        { // pass it to right
            res = inOrder(root->right, prev);
        }
        return res;
    }
    bool isValidBST(TreeNode *root)
    {
        if (!root)
            return true;
        optional<int> prev; // using an optional to deal with the leftMost node
                            // which doesnt have a prev
        return inOrder(root, prev);
    }
};