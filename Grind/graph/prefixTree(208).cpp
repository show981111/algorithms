/**
 * @brief Prefix Tree
 * Each node has a children(represent alphabets) array and boolen isWord.
 * Word is stored as a chain of this nodes!
 */

class Trie
{
public:
    Trie *children[26];
    bool isWord;
    Trie()
    {
        for (int i = 0; i < 26; i++)
            this->children[i] = nullptr;
        isWord = false;
    }

    void insert(string word)
    {
        Trie *cur = this;
        for (char c : word)
        {
            int index = c - 'a';
            if (cur->children[index] == nullptr)   // this node doesn't have a child with this character
                cur->children[index] = new Trie(); // make new one
            cur = cur->children[index];
        }
        cur->isWord = true; // at the last, the word is stored
    }

    bool search(string word)
    {
        Trie *cur = this;
        for (char c : word)
        {
            int index = c - 'a';
            if (cur->children[index] == nullptr)
                return false;
            cur = cur->children[index];
        }
        return cur->isWord;
    }

    bool startsWith(string prefix)
    {
        Trie *cur = this;
        for (char c : prefix)
        {
            int index = c - 'a';
            if (cur->children[index] == nullptr)
                return false;
            cur = cur->children[index];
        }
        return true;
    }
};
