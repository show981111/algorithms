class Solution
{
public:
    void dfs(TreeNode *root, unordered_map<long, int> &sums, long curSum, int targetSum, int &count)
    {
        if (root == nullptr)
            return;
        curSum += root->val;
        // cout << root->val << " " << curSum - targetSum << endl;
        if (sums.find(curSum - targetSum) != sums.end())
        {
            count += sums[curSum - targetSum];
        }
        // if the sum starts from the root, then we should add it
        if (curSum == targetSum)
        {
            count++;
        }

        // should add to the map later because it will count itself
        // if we put this before counting
        sums[curSum]++;
        dfs(root->left, sums, curSum, targetSum, count);
        dfs(root->right, sums, curSum, targetSum, count);

        sums[curSum]--;
    }
    int pathSum(TreeNode *root, int targetSum)
    {
        int count = 0;
        unordered_map<long, int> sums;
        dfs(root, sums, 0, targetSum, count);
        return count;
    }
};