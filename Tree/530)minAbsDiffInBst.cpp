/**
 *
Intuition
Since inorder traversal of the BST is a sorted sequence, we only need to compare the differences with neighbors in inorder sequence.

Approach
    MIN_MAX APPROACH
        So the task is, at each node, get the max of left subtree (inorder predecessor)
        and min of the right subtree (inorder successor) and compute the differences.

        To design the recursive function, that does this task, we can do postorder traversal
        (since we need max from left tree and min from right tree to compute the differences
        with current node) and return the {min node, max node} pair of current tree rooted with cur node.

    Only compare with prev or next
        From the above approach, we compare both predecessor and successor. For example, from this sequence,
        [1,2,<3>,4,5], if we are currently at 3, then we compute difference with both prev num and next num: abs(2-3) and abs(3-4).
        However, this is not necessary. We only need to compare with prev or next number at each node.
        For example, we compute abs(1-2) at 2, abs(2-3) at 3, and abs(3-4) at 4 etc.

        To design the recursive function that does this, we need to pass the current value as a reference.
        Passing the value as a return value in this case is a bit tricky. Passing the current node's value to
        the right subtree's recursive call using a return value is tricky because children does not have an access to parent's return value.
        EX)
            6
           / \
          1  100
             / \
            7  101
         If we are at the root 6, we want to pass 6 to inorder successor, 7. However, if we just use the return value, then
         7 cannot get 6 because 7 does not have an access to call a recursive call on parent. So, we need to pass it as a reference so that
         parent can pass the value to child.

https://leetcode.com/problems/minimum-absolute-difference-in-bst/solutions/4468264/o-n-two-approaches-and-how-to-design-a-recursive-function/
 */

// First approach
class Solution
{
public:
    const int MAXNODE = 200001;
    const int MINNODE = -200001;
    struct Info
    {
        int min;
        int max;
    };
    Info helper(TreeNode *cur, int &ans)
    {
        if (cur == nullptr)
            return {MAXNODE, MINNODE};

        Info prev = helper(cur->left, ans);  // get max from left
        Info next = helper(cur->right, ans); // get min from right

        ans = min(ans, abs(prev.max - cur->val));
        ans = min(ans, abs(next.min - cur->val));
        int maxVal = max(prev.max, max(cur->val, next.max));
        int minVal = min(prev.min, min(cur->val, next.min));
        return {minVal, maxVal};
    }
    int getMinimumDifference(TreeNode *root)
    {
        int ans = 100001;
        helper(root, ans);
        return ans;
    }
};

// Second approach
class Solution
{
public:
    void helper(TreeNode *cur, int &prev, int &ans)
    {
        if (cur == nullptr)
            return;

        helper(cur->left, prev, ans);
        if (prev != -1)
            ans = min(ans, abs(prev - cur->val));
        prev = cur->val;
        helper(cur->right, prev, ans);
    }
    int getMinimumDifference(TreeNode *root)
    {
        int ans = 100001;
        int prev = -1;
        helper(root, prev, ans);
        return ans;
    }
};
