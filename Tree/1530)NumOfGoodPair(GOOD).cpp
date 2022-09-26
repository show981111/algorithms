/**
 * @brief Recursive function
 * It is all about finding a recursive relationship!
 * Start from small subtree and enlarge the view
 *
 * If we do this for subTree, is it repeated for parent tree too?
 * Find the repeated structure of the problem!
 *
 * We need the children list from the subTree to calculate parent Tree
 * => oh! we should return children to use it from parent!
 *
 * If we pass Information from Parent -> Child : use PARAMETER ex) depth.
 * If we pass Information from Child -> Parent : user RETURN value ex)vector<int>
 *
 * (A) get children as a vector, and calculate distance at each root.
 * Then we can update count.
 * (B) Brute force will be make a graph and do BFS from each leaf node.
 */
class Solution
{
public:
    int count = 0;
    vector<int> helper(TreeNode *root, int depth, int dist)
    {
        if (root == nullptr)
        {
            return vector<int>{};
        }
        if (root->left == nullptr && root->right == nullptr)
        {
            return vector<int>{depth};
        }
        // get children from left and right.
        vector<int> left = move(helper(root->left, depth + 1, dist));
        vector<int> right = move(helper(root->right, depth + 1, dist));

        if (left.size() > 0 && right.size() > 0)
        {
            // calculate distance
            for (int i = 0; i < left.size(); i++)
            {
                for (int j = 0; j < right.size(); j++)
                {
                    // if it is a good pair, update count
                    if (abs(left[i] + right[j] - 2 * depth) <= dist)
                    {
                        count++;
                    }
                }
            }
        }
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }

    int countPairs(TreeNode *root, int distance)
    {
        helper(root, 0, distance);
        return count;
    }
};