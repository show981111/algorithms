/**
 * What do we need to do erase in arbitary index & insert operation in O(1) -> List
 * But, List requires O(N) search time.
 * How to get the location of node in O(1)?
 *
 * Map that stores key -> location of the node
 */

class LRUCache
{
public:
    struct Data
    {
        int key;
        int data;
    };

    list<Data> lru;
    int cap;
    unordered_map<int, list<Data>::iterator> keyToDataLoc;

    LRUCache(int capacity) : cap(capacity)
    {
    }

    int get(int key)
    {
        if (keyToDataLoc.count(key) > 0)
        {
            // move to the end of lru
            put(key, keyToDataLoc[key]->data);
            return keyToDataLoc[key]->data;
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (keyToDataLoc.count(key) > 0)
        { // key alr exist
            // move keyToDataLoc[key] to the end of the list
            lru.erase(keyToDataLoc[key]);
        }
        else
        {
            // new key
            if (lru.size() == cap)
            { // evict
                keyToDataLoc.erase(lru.begin()->key);
                lru.pop_front();
            }
        }
        lru.push_back(Data{key, value});
        // update location map
        keyToDataLoc[key] = prev(lru.end(), 1);
    }
};
