/**
 * @brief It is like binarySearch
 * Through Inorder and Preorder, we can figure out which part is
 * leftSubtree or RightSubtree.
 * Thus, we do "build" for each subtree and get Root from them.
 * Then we connect current root and each root of subtree.
 * EASY!
 *
 */

class Solution
{
public:
    // root is the index of root in Preorder
    // left and right is interms or Inorder
    TreeNode *build(vector<int> &pre, vector<int> &in, int root, int left, int right)
    {
        if (left > right)
            return nullptr;
        int leftEndIn = left;
        while (in[leftEndIn] != pre[root])
            leftEndIn++; // 1
        TreeNode *leftRoot = build(pre, in, root + 1, left, leftEndIn - 1);
        TreeNode *cur = new TreeNode(pre[root]);
        // we should cautious when getting the index of rightSubtree
        // Root + left subtree size + 1 = right subtree root
        // root + left subtree size gives the end index of leftSubTree.
        // we should add 1 to get the root if RightSubtree
        TreeNode *rightRoot = build(pre, in, root + leftEndIn - left + 1, leftEndIn + 1, right);
        cur->left = leftRoot;
        cur->right = rightRoot;
        return cur;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return build(preorder, inorder, 0, 0, inorder.size() - 1);
    }
};
