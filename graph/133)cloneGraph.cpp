// BFS

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (!node)
            return node;
        Node *copyList[101];
        for (int i = 0; i < 101; i++)
            copyList[i] = nullptr;

        queue<Node *> q;
        q.push(node);

        Node *head = new Node(node->val);
        copyList[head->val] = head;

        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            for (Node *&n : cur->neighbors)
            {
                if (copyList[n->val] == nullptr)
                {
                    Node *copiedNeighbor = new Node(n->val);
                    q.push(n);
                    copyList[copiedNeighbor->val] = copiedNeighbor;
                }
                copyList[cur->val]->neighbors.push_back(copyList[n->val]);
            }
        }

        return copyList[1];
    }
};

// dfs
class Solution
{
private:
    Node *copyList[101];

public:
    void dfs(Node *cur)
    {
        if (cur == nullptr)
            return;
        copyList[cur->val] = new Node(cur->val);

        for (auto &adj : cur->neighbors)
        {
            if (copyList[adj->val] == nullptr)
            {
                dfs(adj);
            }
            copyList[cur->val]->neighbors.push_back(copyList[adj->val]);
        }
    }

    Node *cloneGraph(Node *node)
    {
        if (!node)
            return node;
        for (int i = 0; i < 101; i++)
            copyList[i] = nullptr;
        dfs(node);
        return copyList[1];
    }
};