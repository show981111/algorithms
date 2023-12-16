/**
 * Ordered Map use .lower_bound !
 *
 * Ordered Container, but I need to access each elem => Use ordered map!
 * PQ cannot access each elem!
 *
 * Can't use monotonic stack since get can request any timestamp!
 */

class TimeMap
{
public:
    unordered_map<string, map<int, string>> mp;
    TimeMap()
    {
    }

    void set(string key, string value, int timestamp)
    {
        mp[key][timestamp] = value;
    }
    // O(logN)
    string get(string key, int timestamp)
    {
        if (mp.count(key) > 0)
        {
            auto iter = mp[key].lower_bound(timestamp); // will return timestamp if exists, otherwise will return something bigger than timestamp
            if (iter != mp[key].end() && iter->first == timestamp)
                return iter->second;
            if (iter != mp[key].begin() && prev(iter, 1)->first < timestamp)
            {
                return prev(iter, 1)->second;
            }
        }
        return "";
    }
};

/**
 * Lower Bound Custom Lambda.
 * (Data, val) {} return true if data goes before val!
 * It returns first elem that Comp is false.
 */

class TimeMap
{
public:
    struct data
    {
        int t;
        string val;
    };
    unordered_map<string, vector<data>> mp;
    TimeMap()
    {
    }

    void set(string key, string value, int timestamp)
    {
        mp[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp)
    {
        if (mp.count(key) > 0)
        {
            auto iter = lower_bound(mp[key].begin(), mp[key].end(), timestamp, [](const data &d, int timestamp)
                                    { return d.t < timestamp; });
            if (iter != mp[key].end() && iter->t == timestamp)
                return iter->val;
            if (iter != mp[key].begin() && prev(iter, 1)->t < timestamp)
                return prev(iter, 1)->val;
        }
        return "";
    }
};