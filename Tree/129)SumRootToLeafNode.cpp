/**
 * Simple pre-order(DFS).
 *
 * Shifting number to the right or left is just dividing/multiplying by 10.
 *
 * Key point of recursive function is the base case.
 * When do we want to stop and computer answer?
 */

class Solution
{
public:
    void sum(TreeNode *cur, int &s, int curNum)
    {
        if (cur == nullptr)
        {
            return;
        }
        curNum = 10 * curNum + cur->val;
        if (cur->left == nullptr && cur->right == nullptr)
        {
            s += curNum;
        }
        sum(cur->left, s, curNum);
        sum(cur->right, s, curNum);
    }
    int sumNumbers(TreeNode *root)
    {
        int s = 0;
        sum(root, s, 0);
        return s;
    }
};