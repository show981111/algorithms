/**
 */
class Solution
{
public:
    TreeNode *build(vector<int> &pre, vector<int> &in, int &preCurIndex, int inStart, int inEnd)
    {
        if (inStart >= inEnd)
        {
            return new TreeNode(in[inStart]);
        }
        if (preCurIndex >= pre.size())
            return nullptr;

        int rootVal = pre[preCurIndex];
        int rootIndexInOrder;
        for (int i = 0; i < in.size(); i++)
            if (in[i] == rootVal)
                rootIndexInOrder = i;
        int leftSubTreeSize = rootIndexInOrder - inStart;
        TreeNode *root = new TreeNode(rootVal);
        root->left = build(pre, in, ++preCurIndex, inStart, rootIndexInOrder - 1);
        root->right = build(pre, in, ++preCurIndex, rootIndexInOrder + 1, inEnd);

        return root;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int preIndex = 0;
        return build(preorder, inorder, preIndex, 0, inorder.size() - 1);
    }
};

// 3 9 10 11 20 15 7,   10 9 11 3 15 20 7