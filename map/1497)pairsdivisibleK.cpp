/*
Couting Problem!
Decisiong problem, no need to know exact pairs.
-> counting?
Also, divisible by "K" => Think about how to use MOD!

Power Of Mod -> only need to think about numbers under that MOD!
*/

class Solution
{
public:
    bool canArrange(vector<int> &arr, int k)
    {
        // brute force -> Try all possible pairs O(N*N) -> Back tracking
        // do not need to know exact pairs... just possible?
        // divisible by K... -> map by "mod"
        unordered_map<int, int> mp;
        /*
        0 -> by themselves
        1 -> with 5
        2 -> with 4
        3
        4
        5
        */
        for (int i = 0; i < arr.size(); i++)
        {
            int key = ((arr[i] % k) + k) % k;
            mp[key]++;
        }
        // for(auto &iter: mp){
        //     cout << iter.first << " : " << iter.second << endl;
        // }
        if (mp[0] % 2 != 0)
            return false;
        if (k % 2 == 0 && mp[k / 2] % 2 != 0)
            return false;
        for (int i = 1; i <= k / 2; i++)
        {
            if (mp[i] != mp[k - i])
                return false;
        }
        return true;
    }
};

class Solution
{
public:
    bool marking(unordered_map<int, bool> &marked, unordered_map<int, vector<int>> &mp, int N)
    {
        if (marked.size() == N)
            return true;

        for (auto &it : mp)
        {
            if (marked.find(it.first) == marked.end())
            {
                for (int i = 0; i < it.second.size(); i++)
                {
                    if (marked.find(it.second[i]) == marked.end())
                    {
                        marked[it.first] = it.second[i];
                        marked[it.second[i]] = it.first;
                        if (marking(marked, mp, N))
                            return true;
                        marked.erase(it.first);
                        marked.erase(it.second[i]);
                    }
                }
            }
        }

        return false;
    }
    bool cleanMp(unordered_map<int, vector<int>> &mp)
    {
        for (auto &it : mp)
        {
            if (it.second.size() == 1)
            {
                int tempVal = it.second[0];
                int key = it.first;
                mp[key].pop_back();
                // mp.erase(key); // that key should be matched with tempVal
                if (mp.find(tempVal) == mp.end())
                    return false;
                std::vector<int>::iterator pos = std::find(mp[tempVal].begin(), mp[tempVal].end(), key);
                if (pos == mp[tempVal].end())
                {
                    return false;
                }
                else
                {
                    mp[tempVal].erase(pos);
                }

                cleanMp(mp);
            }
        }
        return true;
    }
    bool canArrange(vector<int> &arr, int k)
    {
        // brute force -> Try all possible pairs O(N*N) -> Back tracking
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < arr.size(); i++)
        {
            for (int j = i + 1; j < arr.size(); j++)
            {
                if ((arr[i] + arr[j]) % k == 0)
                {
                    mp[i].push_back(j);
                    mp[j].push_back(i);
                }
            }
        }
        if (mp.size() != arr.size())
            return false;
        for (auto &it : mp)
        {
            cout << arr[it.first] << " -> ";
            for (auto elem : it.second)
            {
                cout << arr[elem] << " ";
            }
            cout << endl;
        }
        // unordered_map<int,bool> marked;
        // bool res=  marking(marked, mp, arr.size());
        bool res = cleanMp(mp);
        return res;
    }
};