/**
 * @brief Characteristic of BST
 * In order makes ordered list => Root is the median in balanced Tree
 * BST: For "ALL" nodes, left <= root < right!
 *
 */

class Solution
{
public:
    //[left, right)
    TreeNode *makeBalancedBST(vector<int> &nums, int left, int right)
    {
        if (left >= right) // since [left, right), use left >= right, not ">"
            return nullptr;
        int curIndex = (left + right) / 2;
        TreeNode *curNode = new TreeNode(nums[curIndex]);
        curNode->left = makeBalancedBST(nums, left, curIndex);
        curNode->right = makeBalancedBST(nums, curIndex + 1, right);
        return curNode;
    }
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return makeBalancedBST(nums, 0, nums.size());
    }
};