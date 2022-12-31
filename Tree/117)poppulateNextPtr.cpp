class Solution
{
public:
    /*
            1       prev
         2      3   cur
          4        6
         7  8
    */
    Node *connect(Node *root)
    {
        if (!root)
            return root;
        Node *prevLevel = root;

        while (prevLevel != nullptr)
        {
            Node *prevLevelHead = prevLevel;
            Node *curLevelHead = nullptr;
            Node *cur = nullptr;

            while (prevLevel != nullptr)
            {
                if (curLevelHead == nullptr)
                {
                    if (prevLevel->left)
                    {
                        curLevelHead = prevLevel->left;
                    }
                    else if (prevLevel->right)
                    {
                        curLevelHead = prevLevel->right;
                    }
                    cur = curLevelHead;
                } // find curLevelHead

                if (prevLevel->left && cur != nullptr && cur != prevLevel->left)
                {
                    cur->next = prevLevel->left;
                    cur = cur->next;
                }
                if (prevLevel->right && cur != nullptr && cur != prevLevel->right)
                {
                    cur->next = prevLevel->right;
                    cur = cur->next;
                } // weaving

                prevLevel = prevLevel->next;
            }

            prevLevel = curLevelHead; // go to next level!
        }
        return root;
    }
};