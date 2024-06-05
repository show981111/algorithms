/**
 * In the beginning, used bottom up to collect strings and pass smaller one.
 * However, lexico order is complicated.
 * EX) "abab[z]" < "ab[z]" Since 2nd index, "aba" is smaller.
 *      However, "abab" > "ab"
 * Thus, we should use top down!
 *
 * Recursive function has only two forms.
 * 1) Top-down (pass as parameter) 2) Bottom-up (pass as return)
 */
class Solution
{
public:
    void helper(TreeNode *cur, string prev, string &ans)
    {
        if (cur == nullptr)
            return;
        string s(1, cur->val + 'a');
        s += prev;
        if (cur->left == nullptr && cur->right == nullptr)
        {
            if (ans == "")
                ans = s;
            else
                ans = min(ans, s);
        }
        else
        {
            helper(cur->left, s, ans);
            helper(cur->right, s, ans);
        }
    }
    string smallestFromLeaf(TreeNode *root)
    {
        string ans = "";
        helper(root, "", ans);
        return ans;
    }
};

/**
 * At each level, pushing the character at the front is ineifficient.
 * Can we do better?
 * Anyways, the point that we perform the minimization is only at the leaf level.
 * Why don't we just push_back chars and perform reverse right before we perform
 * update?
 */
class Solution
{
public:
    /*
    A < B, does this mean A.reverse() > B.reverse() ?
    "aba" "ac"
    "aba" > "ca"
    */
    void helper(TreeNode *cur, string prev, string &ans)
    {
        if (cur == nullptr)
            return;
        prev.push_back(cur->val + 'a');
        if (cur->left == nullptr && cur->right == nullptr)
        {
            reverse(prev.begin(), prev.end());
            if (ans == "")
                ans = prev;
            else
                ans = min(ans, prev);
        }
        else
        {
            helper(cur->left, prev, ans);
            helper(cur->right, prev, ans);
        }
    }
    string smallestFromLeaf(TreeNode *root)
    {
        string ans = "";
        helper(root, "", ans);
        return ans;
    }
};
