class Solution
{
public:
    bool dfs(TreeNode *cur, ListNode *head)
    {
        if (head == nullptr)
        {
            return true;
        }
        else if (cur == nullptr)
            return false;

        ListNode *temp = head;
        if (cur->val == head->val)
            temp = temp->next;
        else
            return false;
        // the path should be connected!!!
        // if we do not return false right away, then it will
        // keep traversing the tree...
        // ex) 1 -> 2 -> 4 -> 3, and [1,2,3] will be true by skipping 4.

        bool res = dfs(cur->left, temp);
        if (!res)
            res = dfs(cur->right, temp);
        return res;
    }
    bool isSubPath(ListNode *head, TreeNode *root)
    {
        if (!root)
            return false;
        return dfs(root, head) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }
};