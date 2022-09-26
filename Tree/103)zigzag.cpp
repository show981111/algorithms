/**
 * @brief Remember that when we use stack,
 * then we are popping from the top, so children is popped first
 * than their parents!
 *
 * My first thought => Stack + queue.
 * if we use stack, and pop and inseted to queue,
 * then the order of queue is not what we expected
 * (order is the same as stack's popping order!)
 *
 * Just think which order I should traverse...
 * I should consider pushing order + popping order
 *
 * Can we use one deque?
 * yup...
 * (A) pop_pack(), push_front()
 * (B) pop_front(). push_back()
 */
class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        int level = 0;
        vector<vector<int>> ans;
        stack<TreeNode *> st1; // if level % 2 ==0
        stack<TreeNode *> st2; // if level % 2 ==1
        if (root == nullptr)
            return ans;
        st1.push(root);

        while (!st1.empty() || !st2.empty())
        {
            int levelSize = max(st1.size(), st2.size());
            vector<int> levels;
            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *cur;
                if (level % 2 == 0)
                { // pop from q
                    cur = st1.top();
                    st1.pop();
                    if (cur->left)
                        st2.push(cur->left);
                    if (cur->right)
                        st2.push(cur->right);
                }
                else
                { // pop from st
                    cur = st2.top();
                    st2.pop();
                    if (cur->right)
                        st1.push(cur->right);
                    if (cur->left)
                        st1.push(cur->left);
                }
                levels.push_back(cur->val);
            }
            ans.push_back(levels);
            level++;
        }
        return ans;
    }
};