/**
 * Nice iterator approach
 * https://leetcode.com/problems/leaf-similar-trees/solutions/4532252/c-beats100-iterator-stack-enumeration-clean-approach
 */
class Solution
{
public:
    void getLeaf(TreeNode *cur, vector<int> &leaves)
    {
        if (cur == nullptr)
            return;
        if (!cur->left && !cur->right)
        {
            leaves.push_back(cur->val);
        }
        else
        {
            getLeaf(cur->left, leaves);
            getLeaf(cur->right, leaves);
        }
    }
    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        vector<int> r1Leaf, r2Leaf;
        getLeaf(root1, r1Leaf);
        getLeaf(root2, r2Leaf);
        if (r1Leaf.size() == r2Leaf.size())
        {
            for (int i = 0; i < r1Leaf.size(); i++)
            {
                if (r1Leaf[i] != r2Leaf[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};
