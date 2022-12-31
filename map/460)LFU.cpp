/**
 * @brief We use 2D linked List...
 * FreqList: <Count> - <Count> - <Count>  ...
 *            <Node>    <Node>    <Node>
 *            <Node>
 * How do we make 2D list?
 * Item of list should contain linkedList
 * Node {
 *    T data;
 *    list<T> columnList;
 * }
 *
 * LinkedList -> erase, insert is O(1)!
 *
 * OR
 * we can do with 3 map
 * https://leetcode.com/problems/lfu-cache/discuss/94516/Concise-C++-O(1)-solution-using-3-hash-maps-with-explanation/211361
 *
 * 1: key -> <value, freq>
 * 2: key -> list iterator(in freqToListMap)
 * 3: freq -> list of keys
 *
 * Then we manage minKey value to evict stuff
 * (Tactic is we do not erase freq even though list is empty for that freq
 * We just do minKey++ if that list is empty for freq)
 */

class LFUCache
{
public:
    LFUCache(int capacity)
    {
        this->capacity = capacity;
        freqList.push_back(Count{0, list<Node>()}); // dummy
    }

    int get(int key)
    {
        // cout << "GET " << key << endl;
        if (keyToLoc.find(key) == keyToLoc.end())
        {
            return -1;
        }
        else
        {
            updateRank(key);
            return keyToLoc[key].nLoc->value;
        }
    }

    void put(int key, int value)
    {
        if (capacity == 0)
            return;
        if (keyToLoc.find(key) == keyToLoc.end())
        {
            if (keyToLoc.size() == capacity)
            {
                // cout << "PUT " << key << " => ";
                evict();
            }
            Node data{key, value};
            insert(key, data, freqList.begin(), 1);
        }
        else
        { // exist
            keyToLoc[key].nLoc->value = value;
            updateRank(key);
        }
    }

private:
    struct Node
    {
        int key;
        int value;
        Node() {}
        Node(int k, int v) : key(k), value(v) {}
    };
    struct Count
    {
        int count;
        list<Node> nodes;
        Count() {}
        Count(int c, list<Node> n) : count(c), nodes(n) {}
    };

    typedef list<Count>::iterator CountLoc;
    typedef list<Node>::iterator NodeLoc;

    struct Loc
    {
        CountLoc cLoc;
        NodeLoc nLoc;
    };

    list<Count> freqList; // value, count
    unordered_map<int, Loc> keyToLoc;

    int capacity;

    void evict()
    {
        auto counter = ++freqList.begin();
        // cout << counter->count << " and " << counter->nodes.size() << endl;
        int victimKey = counter->nodes.front().key;
        keyToLoc.erase(victimKey);
        // cout << victimKey << " is evicted \n";
        counter->nodes.pop_front();
        if (counter->nodes.size() == 0)
        {
            // cout<< counter->count << " is gone \n";
            freqList.erase(counter);
        }
    }

    void updateRank(int key)
    {
        Node data = *keyToLoc[key].nLoc;
        CountLoc counter = keyToLoc[key].cLoc;
        int oldCount = counter->count;
        // erase from node list
        counter->nodes.erase(keyToLoc[key].nLoc);
        insert(key, data, counter, oldCount + 1);
        if (counter->nodes.empty())
        { // if its empty remove
            freqList.erase(counter);
        }
    }
    void insert(int key, Node &data, CountLoc counter, int curCount)
    {
        CountLoc freqSpot;
        // cout << "insert " << key << " count " << curCount << endl;
        if (next(counter, 1) == freqList.end())
        { // should set up new count node
            freqList.push_back(Count{curCount, list<Node>()});
            freqSpot = prev(freqList.end(), 1);
        }
        else if (next(counter, 1)->count == curCount)
        { // node already there
            freqSpot = next(counter, 1);
        }
        else if (next(counter, 1)->count > curCount)
        { // next is bigger, should create before this one
            freqList.insert(next(counter, 1), Count{curCount, list<Node>()});
            freqSpot = next(counter, 1);
        }
        else
        { // next cannot be smaller
            assert(false);
        }
        freqSpot->nodes.push_back(data); // add data to new spot
        keyToLoc[key].cLoc = freqSpot;   // set keyToLoc
        keyToLoc[key].nLoc = prev(freqSpot->nodes.end(), 1);
        // cout << key << " insert done \n";
    }
};

/**
 * @brief Failed in case when the frequencies are
 * not consecutive.
 *
 * EX) freq is 1 -> 5 -> 10.
 * If we are trying to update rank of 5,
 * we will look up 6, but it does not exist, so it will push_back to the list.
 * This is problematic. We should implement a way to track next frequency with O(1)
 * => 2D linkedList
 * Frequency => list
 *
 * for the MAP, we should store
 * key => {location in freqMap, location in freq[i]}
 */

class LFUCache
{
public:
    LFUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        if (keyToLoc.find(key) == keyToLoc.end())
        {
            return -1;
        }
        else
        {
            updateRank(key);
            return keyToLoc[key]->value;
        }
    }

    void put(int key, int value)
    {
        if (keyToLoc.find(key) == keyToLoc.end())
        {
            if (valueList.size() == capacity)
            {
                cout << "PUT " << key << " => ";
                evict();
            }
            valueList.push_front(Node{key, value, 0});
            keyToLoc[key] = valueList.begin();
            updateRank(key); // updaet count from 0 to 1
            if (valueList.size() > capacity)
                evict();
        }
        else
        { // exist
            keyToLoc[key]->value = value;
            updateRank(key);
        }
    }

private:
    struct Node
    {
        int key;
        int value;
        int count;
        Node(int k, int v, int c) : key(k), value(v), count(c) {}
    };
    list<Node> valueList; // value, count
    unordered_map<int, list<Node>::iterator> keyToLoc;
    unordered_map<int, list<Node>::iterator> countToHead;
    int capacity;

    void evict()
    {
        if (valueList.empty())
            return;
        auto victim = valueList.begin();
        cout << victim->key << " is evicted " << endl;
        keyToLoc.erase(victim->key); // erase from keyToLoc

        // adjust countToHead
        if (next(victim, 1) != valueList.end() && next(victim, 1)->count == victim->count)
        {
            countToHead[victim->count] = next(victim, 1);
        }
        else if (next(victim, 1) != valueList.end() && next(victim, 1)->count != victim->count)
        {
            countToHead.erase(victim->count);
        }
        else
        {
            countToHead.erase(victim->count);
        }
        valueList.pop_front(); // erase from valueList
    }

    void updateRank(int key)
    {
        int val = keyToLoc[key]->value;
        int oldCount = keyToLoc[key]->count++;
        int newCount = oldCount + 1;
        auto oldLoc = keyToLoc[key];

        if (countToHead[oldCount] == oldLoc)
        {
            if (next(oldLoc, 1)->count == oldCount)
            {
                // there is a multiple elem with this count
                countToHead[oldCount] = next(oldLoc, 1);
            }
            else
            { // no this is the only one.
                cout << " old count " << oldCount << "is erase \n";
                countToHead.erase(oldCount);
            }
        } // update countToHead... only if this location is head

        valueList.erase(oldLoc); // delete elem from oldLocation
        list<Node>::iterator newLoc;

        // set valueList and countToHead
        if (countToHead.find(newCount + 1) == countToHead.end())
        { // nextVal of new Count does not exist
            valueList.push_back(Node{key, val, newCount});
            // PROBLEM!!!!!!! next frequency does not have to be newCount + 1.
            // so we cannot just push_back this
            newLoc = prev(valueList.end(), 1);
        }
        else
        { // exist...
            // insert before nextCount

            valueList.insert(countToHead[newCount + 1], Node{key, val, newCount});
            newLoc = prev(countToHead[newCount + 1], 1);
        }
        cout << key << "'s rank is " << newCount;
        cout << " location is " << distance(newLoc, valueList.begin()) << endl;
        keyToLoc[key] = newLoc; // set KeyToLoc
        // if there is no head for current head, set a new one
        if (countToHead.find(newCount) == countToHead.end())
        {
            countToHead[newCount] = newLoc;
        }
    }
};
