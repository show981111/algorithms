
/**
 * Insert/Delete/getRandom
 * Key observation: Order of element does not matter.
 *
 * We need a vector to retrive element in O(1) => Only vector and unordered_map allow O(1) retrieval
 * However, Remove takes O(N) time.
 * But, we do not care about the order of the element!!!
 * Erasing the end element will take O(1) in vector
 * => Just move the element to erase to the end using SWAP!
 * https://leetcode.com/problems/insert-delete-getrandom-o1/solutions/1377728/real-practical-applications-c-optimal-array-unordered-map-explained-average-time-o-1/?envType=study-plan-v2&envId=top-interview-150
 */

/**
 * Anwser
 */

class RandomizedSet
{
public:
    unordered_map<int, int> mp;
    vector<int> items;
    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        if (mp.count(val) > 0)
            return false;
        items.push_back(val);
        mp[val] = items.size() - 1;
        return true;
    }

    bool remove(int val)
    {
        if (mp.count(val) == 0)
            return false;
        if (mp[val] != items.size() - 1)
        {
            int erasedElemIndex = mp[val];
            swap(items[erasedElemIndex], items[items.size() - 1]);
            mp[items[erasedElemIndex]] = erasedElemIndex;
        }
        mp.erase(val);
        items.pop_back();
        return true;
    }

    int getRandom()
    {
        if (items.size() == 0)
        {
            return -1;
        }
        return items[rand() % items.size()];
    }
};

/**
 *
 * First trial, printing elements sequentirally => not a random
 *
 */
class RandomizedSet
{
public:
    list<int> items;
    typedef list<int>::iterator Pos;
    unordered_map<int, Pos> mp;
    Pos cur;
    RandomizedSet()
    {
        cur = items.begin();
    }

    bool insert(int val)
    {
        if (mp.count(val) > 0)
            return false;
        items.push_back(val);
        mp.insert({val, prev(items.end(), 1)});
        if (cur == items.end())
        {
            cur = items.begin();
            // cout << "* Cur is now at" << *cur << "\n";
        }
        return true;
    }

    bool remove(int val)
    {
        if (mp.count(val) == 0)
            return false;
        if (cur == mp[val])
            next();
        items.erase(mp[val]);
        mp.erase(val);
        if (mp.size() == 0)
            cur = items.end();
        return true;
    }

    int getRandom()
    {
        int temp = *cur;
        next();
        return temp;
    }
    void next()
    {
        ++cur;
        if (cur == items.end())
            cur = items.begin();
        // cout << "Cur is now at" << *cur << "\n";
    }
};
