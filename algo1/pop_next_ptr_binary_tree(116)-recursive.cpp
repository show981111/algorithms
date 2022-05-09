/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
/*
Using Recursive
*/
class Solution
{
public:
    void connectHelper(Node *&l, Node *&r)
    {
        if (l == nullptr)
            return;
        l->next = r;
        connectHelper(l->left, l->right);
        connectHelper(l->right, r->left);
        connectHelper(r->left, r->right);
    }

    Node *connect(Node *root)
    {
        if (!root)
            return nullptr;
        connectHelper(root->left, root->right);
        return root;
    }
};