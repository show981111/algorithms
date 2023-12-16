/**
 * Similar to LRU.
 *
 * We want to erase the item at I_th index in O(1) => List
 *
 * We need to keep the counter for each item.
 * Here, map is from count -> list of items. And Item is in the order of LRU.
 * Similary, we keep the location of item in keyToLoc Map.
 *
 * When we evict, we get the lowestCnt by iterating the counter map. -> CAN BE IMPROVED?
 *
 * CPP fact. List is bidirectional iterator so prev will take O(d) for distance
 */
class LFUCache
{
public:
    struct Item
    {
        int key;
        int data;
        int cnt;
    };
    unordered_map<int, list<Item>> cntToItems;
    unordered_map<int, list<Item>::iterator> keyToLoc;
    int cap;
    // int lowestCnt = 0;

    LFUCache(int capacity) : cap(capacity)
    {
    }

    int get(int key)
    {
        if (keyToLoc.count(key) > 0)
        {
            put(key, keyToLoc[key]->data); // update the counter
            return keyToLoc[key]->data;
        }
        return -1;
    }

    int getLowestCnt()
    {
        int ans = INT_MAX;
        for (auto &item : cntToItems)
        {
            ans = min(ans, item.first);
        }
        return ans;
    }

    void put(int key, int value)
    {
        if (keyToLoc.count(key) > 0)
        { // alr exist
            Item temp = *keyToLoc[key];
            // erase that element from that counter's list.
            cntToItems[temp.cnt].erase(keyToLoc[key]);
            if (cntToItems[temp.cnt].size() == 0) // if list is empty for that counter, remove that counter
                cntToItems.erase(temp.cnt);
            temp.cnt++; // update cnt
            temp.data = value;
            cntToItems[temp.cnt].push_back(temp);                // push it to the end of the updated counter
            keyToLoc[key] = prev(cntToItems[temp.cnt].end(), 1); // updated loc
        }
        else
        { // new item
            if (keyToLoc.size() == cap)
            {
                // need to evict
                int lowestCnt = getLowestCnt();
                // if(cntToItems[lowestCnt].size() == 0){
                //     cout << "WTF\n";
                //     cout << lowestCnt << endl;
                // }
                // get an item to evict
                Item victim = cntToItems[lowestCnt].front();
                cntToItems[lowestCnt].pop_front();     // evict
                if (cntToItems[lowestCnt].size() == 0) // if counter is empty, remove
                    cntToItems.erase(lowestCnt);
                keyToLoc.erase(victim.key); // erase from the keyToLoc since that item is removed
            }
            cntToItems[1].push_back(Item{key, value, 1}); // insert new item
            keyToLoc[key] = prev(cntToItems[1].end(), 1); // set keyToLoc for new item
        }
    }
};

/**
 * Well if we think about it,,, lowestCnt doesn't have to be calculated over and over again
 *
 * Key observation
 * 1) When does lowestCnt change? : When the counter is updated due to put or get.
 *      If the list of items for lowestCnt becomes empty due to the update in count, what should be the next lowestCnt?
 *      -> It will just become lowestCnt + 1. When we update the cnt for an item, cnt beomces cnt + 1.
 *         In order to make lowestCnt to get changed, that item's previous cnt should equal to the lowestCnt. Why? unless list for lowestCnt will not change.
 *         Therefore, always the next lowestCnt we should set is just lowestCnt + 1
 * 2) Count always increase by one.
 * 3) Eviction happens "only" when the new element comes in. -> new elment becomes the lowestCnt which is 1
 */

class LFUCache
{
public:
    struct Item
    {
        int key;
        int data;
        int cnt;
    };
    unordered_map<int, list<Item>> cntToItems;
    unordered_map<int, list<Item>::iterator> keyToLoc;
    int cap;
    int lowestCnt = 0;

    LFUCache(int capacity) : cap(capacity)
    {
        lowestCnt = -1;
    }

    int get(int key)
    {
        if (keyToLoc.count(key) > 0)
        {
            put(key, keyToLoc[key]->data);
            return keyToLoc[key]->data;
        }
        return -1;
    }

    int getLowestCnt()
    {
        int ans = INT_MAX;
        for (auto &item : cntToItems)
        {
            ans = min(ans, item.first);
        }
        return ans;
    }

    void put(int key, int value)
    {
        if (keyToLoc.count(key) > 0)
        { // alr exist
            Item temp = *keyToLoc[key];
            cntToItems[temp.cnt].erase(keyToLoc[key]);
            if (cntToItems[temp.cnt].size() == 0)
            {
                if (lowestCnt == temp.cnt)
                { // If lowestCnt's list becomes empty, update it by += 1
                    lowestCnt = temp.cnt + 1;
                }
                cntToItems.erase(temp.cnt);
            }
            temp.cnt++; // update cnt
            temp.data = value;
            cntToItems[temp.cnt].push_back(temp);
            keyToLoc[key] = prev(cntToItems[temp.cnt].end(), 1);
        }
        else
        { // new item
            if (keyToLoc.size() == cap)
            {
                // need to evict
                // lowestCnt == getLowestCnt()
                // if(cntToItems[lowestCnt].size() == 0){
                //     cout << "WTF\n";
                //     cout << lowestCnt << endl;
                // }
                Item victim = cntToItems[lowestCnt].front();
                cntToItems[lowestCnt].pop_front();
                if (cntToItems[lowestCnt].size() == 0)
                    cntToItems.erase(lowestCnt);
                keyToLoc.erase(victim.key);
            }
            lowestCnt = 1; // new element came in. Just update it to 1.
            cntToItems[1].push_back(Item{key, value, 1});
            keyToLoc[key] = prev(cntToItems[1].end(), 1);
        }
    }
};
