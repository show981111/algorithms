class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;
        unordered_map<Node *, Node *> mp; // ptr in original list -> ptr in copied list
        Node *cur = head;
        mp[cur] = new Node(cur->val);
        // setting next ptr
        while (cur != nullptr)
        {
            if (cur->next != nullptr)
            {
                mp[cur]->next = new Node(cur->next->val);
                mp[cur->next] = mp[cur]->next;
            }
            cur = cur->next;
        }
        // setting random ptr
        cur = head;
        while (cur != nullptr)
        {
            mp[cur]->random = mp[cur->random];
            cur = cur->next;
        }
        return mp[head];
    }
};