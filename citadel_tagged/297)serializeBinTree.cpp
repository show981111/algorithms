/**
 * Pre-order and Post-order are Unique!
 * If we specify null nodes!
 *
 * Key observation of serialized string
 *
 * --->
 * 1 2 N N 3 4 N N 5 N N
 *
 * Always root comes at 0-index.
 * Then left child follows, after left subtree showed up, right child follows!
 */
class Codec
{
public:
    void preOrder(TreeNode *cur, string &s)
    {
        if (cur == nullptr)
        {
            s += "N ";
            return;
        }
        s += (to_string(cur->val) + " ");
        preOrder(cur->left, s);
        preOrder(cur->right, s);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string s;
        preOrder(root, s);
        return s;
    }

    int helper(vector<TreeNode *> &nodes, int curIndex)
    {
        if (nodes[curIndex] == nullptr)
            return curIndex;

        if (curIndex + 1 < nodes.size())
        {
            nodes[curIndex]->left = nodes[curIndex + 1];
            int leftEnd = helper(nodes, curIndex + 1);   // left subtree ends here
            nodes[curIndex]->right = nodes[leftEnd + 1]; // set right child to be the next of left subtree.
            int rightEnd = helper(nodes, leftEnd + 1);   // record right end
            return rightEnd;                             // this is the end of current subtree!
        }
        else
        {
            return -1;
        }
    }
    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        istringstream ss(data);
        string w;
        vector<TreeNode *> v;
        while (ss >> w)
        {
            if (w == "N")
                v.push_back(nullptr);
            else
            {
                v.push_back(new TreeNode(stoi(w)));
            }
        }
        helper(v, 0);
        return v[0];
    }
};

/**
 * Post Order Version
EX)                 <---- From root
    N N 2 N N 4 N N 5 3 1
Post order is just a reverse of pre-order.
Last index would be a root always.
Then right child would come right before.
After all right subtree showed up, left child would come.
 */
class Codec
{
public:
    void postOrder(TreeNode *cur, string &s)
    {
        if (cur == nullptr)
        {
            s += "N ";
            return;
        }
        postOrder(cur->left, s);
        postOrder(cur->right, s);
        s += to_string(cur->val) + " ";
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string s;
        postOrder(root, s);
        return s;
    }

    int helper(vector<TreeNode *> &nodes, int curIndex)
    {
        if (nodes[curIndex] == nullptr)
            return curIndex;

        nodes[curIndex]->right = nodes[curIndex - 1];
        int rightEnd = helper(nodes, curIndex - 1);
        nodes[curIndex]->left = nodes[rightEnd - 1];
        int leftEnd = helper(nodes, rightEnd - 1);
        return leftEnd;
    }
    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        istringstream ss(data);
        string w;
        vector<TreeNode *> v;
        while (ss >> w)
        {
            if (w == "N")
                v.push_back(nullptr);
            else
            {
                v.push_back(new TreeNode(stoi(w)));
            }
        }
        helper(v, v.size() - 1);
        return v.back();
    }
};
