class Solution
{
public:
    bool traverse(TreeNode *root, unordered_map<int, TreeNode *> &nodes, unordered_map<int, pair<TreeNode *, int>> &nums, int mini, int maxi)
    {
        if (root == nullptr)
            return true;

        if (root->val < mini || root->val > maxi)
            return false;
        if (nums.find(root->val) == nums.end()) // already visited
            return false;
        nums.erase(root->val);
        bool res = true;

        if (root->left)
        {
            // cout << root->left->val << endl;
            root->left = nodes[root->left->val]; // connect
            res = traverse(root->left, nodes, nums, mini, root->val);
            if (!res)
                return res;
        }
        if (root->right)
        {
            // cout << root->right->val << endl;
            root->right = nodes[root->right->val];
            res = traverse(root->right, nodes, nums, root->val, maxi);
        }

        return res;
    }
    TreeNode *canMerge(vector<TreeNode *> &trees)
    {
        int N = trees.size();
        unordered_map<int, TreeNode *> nodes;
        unordered_map<int, pair<TreeNode *, int>> nums;
        TreeNode *root = nullptr;
        for (int i = 0; i < N; i++)
        {
            int rootVal = trees[i]->val;
            nums[rootVal].first = trees[i];
            nums[rootVal].second++;

            nodes[rootVal] = trees[i];
            if (trees[i]->left)
            {
                nums[trees[i]->left->val].second++;
                if (nodes.find(trees[i]->left->val) == nodes.end())
                {
                    nodes[trees[i]->left->val] = trees[i]->left;
                }
            }
            if (trees[i]->right)
            {
                nums[trees[i]->right->val].second++;
                if (nodes.find(trees[i]->right->val) == nodes.end())
                {
                    nodes[trees[i]->right->val] = trees[i]->right;
                }
            }
        }
        for (auto &iter : nums)
        {
            if (iter.second.first != nullptr && iter.second.second == 1)
                root = iter.second.first;
            // root should be unique and not a leaf node!
        }
        if (root == nullptr)
            return nullptr;

        bool isValid = traverse(root, nodes, nums, INT_MIN, INT_MAX);

        return isValid && nums.size() == 0 ? root : nullptr;
    }
};

/**
[[2,null,3],[5,1],[4,2],[1,null,4]]
[[2,1],[3,2,5],[5,4]]
[[2,1,3]]
[[3,2,5],[2,1],[5,4]]
*/