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

class Solution
{
public:
    Node *connect(Node *root)
    {
        if (!root)
            return root;
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int curLevelSize = q.size(); // size of current level
            Node *cur;
            for (int i = 0; i < curLevelSize; i++) // adding children
            {
                cur = q.front();
                q.pop();
                if (i != curLevelSize - 1)
                    cur->next = q.front();
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            cur->next = nullptr;
        }
        return root;
    }
};