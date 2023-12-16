/**
 * By tracking previous node in Inorder traversal!
 *
 * Caution: when nullptr is returned, (left or right is empty) -> need to return previous "prev" or cur!
 *
 * If there is no left subtree, we should return keep the "prev" since it hasn't changed
 * If there is no right subtree, we should return current since the next recursive call should receive current value not the nullptr.
 */

Node *inOrder(Node *cur, Node *prev, const Node *target, Node *&ans)
{
    if (cur == nullptr)
        return nullptr;
    Node *left = inOrder(cur->left, prev, target, ans);
    if (left != nullptr) // if there is a left subtree, prev is updated since we go deeper into left subtree and prev will be updated
        prev = left;
    if (prev == target && ans == nullptr)
    {
        ans = cur;
    }

    Node *right = inOrder(cur->right, cur, target, ans);

    if (right != nullptr) // if there is a right subtree, we should return the right since this will be the last inorder node of this subtree.
        return right;
    else
        return cur;
}

Node *findSuccessor(Node *root, Node *p)
{
    Node *ans = nullptr;
    inOrder(root, nullptr, p, ans);
    return ans;
}

/**
 * Using a referenced Boolean
 *
 * Ref is easy since it will be turned on once (when we met target)
 */

void inOrder(Node *cur, bool &found, const Node *target, Node *&ans)
{
    if (cur == nullptr)
        return;
    inOrder(cur->left, found, target, ans);
    if (found && ans == nullptr)
    {
        ans = cur;
    }
    if (cur == target)
    {
        found = true;
    }
    inOrder(cur->right, found, target, ans);
}

Node *findSuccessor(Node *root, Node *p)
{
    bool f = false;
    Node *ans = nullptr;
    inOrder(root, f, p, ans);
    return ans;
}