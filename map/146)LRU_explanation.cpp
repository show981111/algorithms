/**
 * @keyToVal
 * @keyToLoc: key to location in list
 * @recentlyUsedOrderQueue: Queue of the key ordered in time
 * (Least Recent) ------- Time -------> (Most Recent)
 *                   [A] - [B] - [C]
 *                   [A] - [B] - [C] - [D] : Access D
 *                   [A] - [C] - [D] - [B] : Access B -> Remove [B] and add [B] to the Back
 *                                            Key challenge is how to remove B in O(1)?
 *                                            If I use vector, no matter what O(N)
 *                                            Use LIST! But problem is, searching the Key(getting the location)
 *                                            is O(N). So use a Map to store the location!
 */

class LRUCache
{
public:
    int cap;
    unordered_map<int, int> keyToVal;
    unordered_map<int, list<int>::iterator> keyToLoc;
    list<int> recentlyUsedOrderQueue;
    LRUCache(int capacity) : cap(capacity)
    {
    }

    int get(int key)
    { // O(1)
        if (keyToVal.find(key) != keyToVal.end())
        {
            put(key, keyToVal[key]);
            return keyToVal[key];
        }
        else
            return -1;
    }

    void put(int key, int value) // O(1)
    {
        keyToVal[key] = value;
        if (keyToLoc.find(key) != keyToLoc.end()) // O(1)
        {                                         // already in a queue
            auto loc = keyToLoc[key];
            // erase in list takes O(1)
            recentlyUsedOrderQueue.erase(loc); // erase it from the previous location. Need to bump up the priority
        }
        // Add it to the back of the queue
        recentlyUsedOrderQueue.push_back(key);                 // O(1)
        keyToLoc[key] = prev(recentlyUsedOrderQueue.end(), 1); // O(1)

        if (recentlyUsedOrderQueue.size() > cap)
        { // remove recently used one.
            int toBeDeletedKey = recentlyUsedOrderQueue.front();
            recentlyUsedOrderQueue.pop_front(); // O(1) - erase in list
            keyToVal.erase(toBeDeletedKey);     // O(1)
            keyToLoc.erase(toBeDeletedKey);     // O(1)
        }
    }
};
