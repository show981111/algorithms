/**
Just getting LCA
Look for Left subtree, if there is one,
Look for Right subtree, if there is one.
if Left and Right are both not null then that root is a LCA.
Other than, keep returning not-null pointer 

What if one node is not in the part of tree? 
we should add something like pFound, qFound, and should check both 
nodes are found

=> LCA application, distance between two node.
*/

class Solution {
public:
    TreeNode* getLCA(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root == nullptr)
            return nullptr;
        if(root == p || root == q)
            return root;
        TreeNode* l = getLCA(root->left, p,q);
        TreeNode* r = getLCA(root->right, p,q);
        if(l != nullptr && r != nullptr)
            return root;
        if(l)
            return l;
        if(r)
            return r;
        return nullptr;
        
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return getLCA(root,p,q);
    }
};

/**
Calculating DIstance between Two nodes
= depth(A) + depth(B) - 2*depth(LCA of A and B)
*/
class Solution {
public:
    pair<TreeNode*,int> getLCA(TreeNode* root, TreeNode* p, TreeNode* q, int depth){
        if(root == nullptr)
            return {nullptr, depth};
        // if(root == p || root == q)
        //     return {root, depth};
        pair<TreeNode*,int> left = getLCA(root->left, p, q, depth+1);
        pair<TreeNode*,int> right = getLCA(root->right, p, q, depth+1);
        
        // cout <<"ROOT " << root->val <<left.second << " " << right.second << endl;

        if(root == p || root == q){
            if(left.first != nullptr)
                return {root, left.second - depth};
            else if(right.first != nullptr){
                return {root, right.second - depth};
            }
            else
                return {root, depth};
        }
        if(left.first != nullptr && right.first != nullptr)
            return {root, left.second + right.second - 2*depth};
        else if(left.first)
            return {left.first, left.second};
        else
            return {right.first, right.second};
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pair<TreeNode*,int> res = getLCA(root,p,q,0);
        // cout << res.second;
        return res.first;
    }
};