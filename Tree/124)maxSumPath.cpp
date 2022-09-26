

/**
 * @brief Return value : Track Downward path sum
 * Ref value : Track diameter paths
 *
 */

class Solution
{
public:
    int helper(TreeNode *root, int &maxSum)
    {
        if (!root)
            return 0;
        int l = helper(root->left, maxSum);
        int r = helper(root->right, maxSum);
        int curDownWardPathSum = max(root->val, max(l + root->val, r + root->val));
        maxSum = max(maxSum, max(curDownWardPathSum, l + r + root->val));
        return curDownWardPathSum;
    }
    int maxPathSum(TreeNode *root)
    {
        int ans = INT_MIN;
        helper(root, ans);
        return ans;
    }
};

/**/**
 * @brief 
 * 
 */
 * dfsGetMax calculate the max path of downWard path
 * DP[TreeNode] = value.
 * the maximum downWard path sum from TreeNode.
 */
class Solution
{
public:
    unordered_map<TreeNode *, int> dp;
    void dfsGetMax(TreeNode *root, int curSum, int &maxSum)
    {
        if (!root)
            return;
        if (dp.find(root) != dp.end())
        {
            maxSum = max(dp[root] + curSum, maxSum);
            return;
        }
        curSum += root->val;
        maxSum = max(curSum, maxSum);
        dfsGetMax(root->left, curSum, maxSum);
        dfsGetMax(root->right, curSum, maxSum);
    }
    void helper(TreeNode *root, int &maxSum)
    {
        if (!root)
            return;

        helper(root->left, maxSum);
        helper(root->right, maxSum);

        int leftSum = INT_MIN;
        dfsGetMax(root->left, 0, leftSum);
        dp[root->left] = leftSum;
        int rightSum = INT_MIN;
        dfsGetMax(root->right, 0, rightSum);
        dp[root->right] = rightSum;

        int curSum;
        if (leftSum == INT_MIN && rightSum == INT_MIN)
            curSum = root->val;
        else if (leftSum == INT_MIN)
            curSum = max(rightSum + root->val, root->val);
        else if (rightSum == INT_MIN)
            curSum = max(leftSum + root->val, root->val);
        else
            curSum = max(leftSum + root->val + rightSum, max(leftSum + root->val, max(root->val + rightSum, root->val)));
        maxSum = max(maxSum, curSum);
        // return curSum;
    }
    int maxPathSum(TreeNode *root)
    {
        int ans = INT_MIN;
        helper(root, ans);
        return ans;
    }
};