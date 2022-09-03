class TimeMap
{
public:
    TimeMap()
    {
    }

    void set(string key, string value, int timestamp)
    {
        mp[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp)
    {
        if (mp.find(key) != mp.end())
        {
            auto it = upper_bound(mp[key].begin(), mp[key].end(), timestamp, [](const int &val, const pair<int, string> &a)
                                  { return val < a.first; });
            it = prev(it);
            if (it - mp[key].begin() >= 0 && it != mp[key].end() && it->first <= timestamp)
            {
                return (it)->second;
            }
            else
            {
                return "";
            }
        }
        else
        {
            return "";
        }
    }

private:
    unordered_map<string, vector<pair<int, string>>> mp;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */