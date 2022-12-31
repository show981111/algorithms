/**
 * @brief https://www.educative.io/answers/how-to-perform-an-iterative-inorder-traversal-of-a-binary-tree
 * Inorder traversal with STACK
 * 1) first push all cur->left until it is null,
 * 2) if it is null, pop<CHECKED!> and push right element.
 * 3) set that right elem as cur and start from (1)
 *
 * In short, push left elems as much as we can, then pop the top.
 * then for right elem of popped elem, push left as much as we can
 * repeat
 *
 * TC: O(1) (AVG) WORST is O(h)
 * We push N elemement to stack and all elems are pushed only once.
 * AVG O(1)
 * SC: O(h)
 */

class BSTIterator
{
public:
    stack<TreeNode *> st;
    BSTIterator(TreeNode *root)
    {
        fill(root);
    }

    int next()
    {
        TreeNode *t = st.top();
        st.pop();
        fill(t->right);
        return t->val;
    }

    bool hasNext()
    {
        if (st.empty())
            return false;
        return true;
    }
    void fill(TreeNode *cur)
    {
        if (cur == nullptr)
            return;
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }
    }
};