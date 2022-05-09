/**
 * @brief
 * Basic Level Order : BFS for binary tree
 * Calculate Level Size by adding all children and popping all parents.
 * => can get the size of all nodes in that level
 */
// perfect binary tree
class Solution
{
public:
    Node *connect(Node *root)
    {
        if (root == nullptr)
            return root;
        queue<Node *> q;
        q.push(root);
        int levelSize = q.size();
        while (!q.empty())
        {
            Node *front;
            while (levelSize--) // current level size
            {
                front = q.front();
                q.pop(); // remove all nodes that is from current level
                front->next = q.front();
                if (front->left) // adding nodes from next level
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            front->next = nullptr; // last item at the level
            levelSize = q.size();  // get the levelSize for next level. Queue only contains next level's nodes.
        }
        return root;
    }
};