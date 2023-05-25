/**
 * @brief Find target contiguous sum in the path.
 *
 * Using a MAP to store the running total.
 * What we want is, current running total - targetSum
 * => sum[i:j] = RunningTotal[j] - RunningTotal[i-1], we want sum[i:j] = targetSum,
 * RunningTotal[j] - RunningTotal[i-1] = targetSum,
 * RunningTotal[j] - targetSum = <RunningTotal[i-1]>
 *
 * Therefore, basically we want to find that if we had the running total of "current running total - targetSum" before!
 * This is the question we want to ask.
 * => Using a MAP to store and retrieve that in O(1)!
 *
 * TC: O(N)!
 *
 */

class Solution
{
public:
    void dfs(TreeNode *cur, unordered_map<long, int> &sumRecord, long targetSum, long prevSum, int &count)
    {
        if (cur == nullptr)
            return;
        long curSum = prevSum + cur->val;
        count += sumRecord[curSum - targetSum]; // find the number from previosu records
        sumRecord[curSum]++;

        dfs(cur->left, sumRecord, targetSum, curSum, count);
        dfs(cur->right, sumRecord, targetSum, curSum, count);

        sumRecord[curSum]--;
    }
    int pathSum(TreeNode *root, int targetSum)
    {
        // 10 5 3 3
        // 10 15 -18
        // FIND curAccumSum - targetSum
        int count = 0;
        unordered_map<long, int> sumRecord;
        sumRecord[0] = 1; // For match from the root
        dfs(root, sumRecord, targetSum, 0, count);
        return count;
    }
};

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

/**
 * @brief Brute Force
 * Record sums from all nodes!
 * sums vertor represents, accumulated sum from 0th, 1th, 2th, 3th ... i_th node
 *
 * TC: O(N^2)
 */

class Solution
{
public:
    void dfs(TreeNode *root, vector<long> &sums, int targetSum, int &count)
    {
        if (root == nullptr)
            return;

        for (long &sum : sums)
        {
            sum += root->val;
            if (sum == targetSum)
            {
                count++;
            }
        }
        if (root->val == targetSum)
            count++;

        sums.push_back(root->val);
        dfs(root->left, sums, targetSum, count);
        dfs(root->right, sums, targetSum, count);

        for (long &sum : sums)
        {
            sum -= root->val;
        }
        sums.pop_back();
    }
    int pathSum(TreeNode *root, int targetSum)
    {
        int count = 0;
        vector<long> sums;
        dfs(root, sums, targetSum, count);
        return count;
    }
};