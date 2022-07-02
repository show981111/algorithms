/**
 * @brief Get MAX Diameter
 *
 * Max diameter at current node = height of left subtree + height of right subtree
 * So we just keep tracking the max value while calculating this maxDiameter per each node!
 */

class Solution
{
public:
    int getHeight(TreeNode *root)
    {
        if (!root)
            return 0;
        else
            return max(getHeight(root->left), getHeight(root->right)) + 1;
    }

    pair<int, int> maxDia(TreeNode *root)
    { //<dia, height>
        if (!root)
            return {0, 0};
        pair<int, int> lDia = maxDia(root->left);
        pair<int, int> rDia = maxDia(root->right);
        int curDia = lDia.second + rDia.second;
        int curHeight = max(lDia.second, rDia.second) + 1;
        return {max(curDia, max(lDia.first, rDia.first)), curHeight};
    }

    int getHeightWhileTrackingMaxDia(TreeNode *root, int &ans)
    {
        if (!root)
            return 0;
        int leftHeight = getHeightWhileTrackingMaxDia(root->left, ans);
        int rightHeight = getHeightWhileTrackingMaxDia(root->right, ans);
        ans = max(ans, leftHeight + rightHeight);
        return max(leftHeight, rightHeight) + 1;
    }

    int diameterOfBinaryTree(TreeNode *root)
    {
        /**
         * @brief First Method : using A getHeight
         * In each call, calculate heights
         */
        if (!root)
            return 0;
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        int curDiameter = leftHeight + rightHeight;
        int lDia = diameterOfBinaryTree(root->left);
        int rDia = diameterOfBinaryTree(root->right);

        return max(curDiameter, max(lDia, rDia));

        /**
         * @brief Second Method : using a Pair
         * calculating height and diameter at the same time
         */
        return maxDia(root).first;

        /**
         * @brief Third Method(BEST)
         * calculating height, but tracking the max one by using a reference value!
         */

        int ans = 0;
        getHeightWhileTrackingMaxDia(root, ans);
        return ans;
    }
};