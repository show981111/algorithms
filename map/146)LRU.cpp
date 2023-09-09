/**
 * @brief LRU
 * Brute Force O(N)
 *      The list that shows me the sequence of accessing elements.
 *      Have a vector of keys.
 *      Each time we access element, push_back to the vector or if that key is already in a vector,
 *      then erase it(shift it) and push element to the last(update the location in the sequence)
 *      -> O(N)
 *      ## BOTTLENECK is Updating the position of element
 *          A) Finding the position of element(O(N))
 *          B) Deleting the element in the sequence(O(N))
 *          C) push that element to the back of the sequence(O(1))
 *
 *      => how can we find the position in O(1)? -> hashTable
 *      => how can we delete the element by position in O(1)? -> list
 *
 * Optimal Alogirthm
 *  Hashtable + List
 *  We have a hashtable, key => position in the list.
 *  Then we have a list of pair<int,int> (key and value)
 *
 */
class LRUCache
{
public:
    LRUCache(int capacity) : capacity(capacity)
    {
    }

    int get(int key)
    {
        if (mp.find(key) == mp.end())
            return -1;
        else
        {
            pair<int, int> datum = make_pair(mp[key]->first, mp[key]->second);
            data.erase(mp[key]);
            data.push_front(datum);
            mp[key] = data.begin();
            return datum.second;
        }
    }

    void put(int key, int value)
    {
        if (mp.find(key) == mp.end())
        {
            // create elem
            pair<int, int> datum = make_pair(key, value);
            if (mp.size() >= capacity)
            { // should evict
                // last element should be erased
                int deletedKey = data.back().first;
                // evict
                mp.erase(deletedKey);
                data.pop_back();
            }
            // push to dataList
            data.push_front(datum);
            // set location map
            mp[key] = data.begin();
        }
        else
        {
            mp[key]->second = value; // update value
            // copy elem to relocate this element to the front of the list
            pair<int, int> datum = make_pair(mp[key]->first, mp[key]->second);
            data.erase(mp[key]);
            data.push_front(datum);
            mp[key] = data.begin();
        }
    }

private:
    unordered_map<int, list<pair<int, int>>::iterator> mp; // key => location in list
    list<pair<int, int>> data;                             // key, value pair
    int capacity;
};

/**
 * OLD way
 * O(N)
 */

class LRUCache
{
public:
    LRUCache(int capacity) : capacity(capacity)
    {
    }

    int get(int key)
    {
        if (mp.find(key) == mp.end())
            return -1;
        else
        {
            shift(key);
            q.push_back(key);
            return mp[key];
        }
    }

    void put(int key, int value)
    {
        if (mp.find(key) == mp.end())
        {
            mp[key] = value; // push to the map

            // cannot use q.size() here because
            // map includes key which just got pushed but q does not take this account
            if (mp.size() > capacity)
            {
                mp.erase(q[0]);
                shift(q[0]);
            }
            q.push_back(key);
        }
        else
        {
            mp[key] = value;
            shift(key);
            q.push_back(key);
        }
    }

private:
    unordered_map<int, int> mp; // key => (val, usedAt)
    int capacity;
    vector<int> q;

    int find(int key)
    {
        for (int i = 0; i < q.size(); i++)
        {
            if (q[i] == key)
                return i;
        }
        return -1;
    }

    void shift(int key)
    {
        int index = find(key);
        if (index != -1)
        {
            for (int i = index; i < q.size() - 1; i++)
            {
                q[i] = q[i + 1];
            }
            q.pop_back();
        }
    }
};
