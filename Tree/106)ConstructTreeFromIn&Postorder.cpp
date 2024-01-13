/**
 * Intuition
Constructing a binary tree is intuitively recursive. We construct a LeftSubTree, RightSubTree and a root node. Then, we connect them.

Process of constructing a tree == constructing a LeftSubTree == constructing a RightSubTree.

Thus, we recursively apply the construct() to leftSubTree and rightSubTree, and connect them.

Key observation here is the structure of the inorder and preorder traversal. In Inorder traversal, we traverse left subtree, root, and right subtree. In postorder traversal, we traverse left subtree, right subtree, and root. For example,

inorder = [9,3,15,20,7] : [left] root [right] => [9] [3] [15,20,7]
postorder = [9,15,7,20,3] : [left] [right] root => [9] [15,7,20] [3]

So we can split an array by indices and construct a tree accordingly.
Left = inorder, preorder: [9]
Root = inorder, preorder: [3]
Right = inorder: [15,20,7], preorder: [15,7,20]
For right subtree, if we go another step of recursion,
Left = [15] Root = [20] Right = [7]

https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solutions/4462878/o-n-recursive-approach-key-observation-to-design-a-recursive-function/
*/
class Solution
{
public:
    // given array inorder[inOrderLeft : InOrderRight], postOrder[pOrderLeft : pOrderRight], construct a tree and return a head
    TreeNode *construct(const vector<int> &inorder, const vector<int> &postorder, unordered_map<int, int> &nodeToIndex,
                        int inOrderLeft, int inOrderRight, int pOrderLeft, int pOrderRight)
    {
        if (inOrderLeft > inOrderRight || pOrderLeft > pOrderRight)
            return nullptr;
        TreeNode *root = new TreeNode(postorder[pOrderRight]);
        int rootIndexInOrder = nodeToIndex[postorder[pOrderRight]];
        int leftSubTreeSize = rootIndexInOrder - inOrderLeft; // +1 -1 (subtract root)

        root->left = construct(inorder, postorder, nodeToIndex, inOrderLeft, rootIndexInOrder - 1, pOrderLeft, pOrderLeft + leftSubTreeSize - 1);
        root->right = construct(inorder, postorder, nodeToIndex, rootIndexInOrder + 1, inOrderRight, pOrderLeft + leftSubTreeSize, pOrderRight - 1);

        return root;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        /*
        inorder   = [9,3,15,20,7] : [left] root [right]
        postorder = [9,15,7,20,3] : [left] [right] root, last one is root
        */
        unordered_map<int, int> nodeToIndex;
        for (int i = 0; i < inorder.size(); i++)
            nodeToIndex[inorder[i]] = i;
        // Since each node is unique (by problem constraint) build a map to fast lookup of the index
        return construct(inorder, postorder, nodeToIndex, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }
};