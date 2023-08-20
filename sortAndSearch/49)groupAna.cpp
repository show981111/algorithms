/**
 * @brief Sorting Finite Amount of elements ex) letters
 *          (Each element could be matched to 0 ~ N) -> only finite possibility for each element
 * Then we can use Counting Sort! -> O(N)
 *
 * (1) Count frequency
 * (2) Iterate from the beginning and copy frequency amount of key
 * (3) Result is sorted!
 *
 * Move Constructor to avoid unnecessary copy!
 * If we are not going to use that elem, just do res.push_back(move(str))!
 * Will prevent copying str.
 */

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> mp;

        for (auto &str : strs)
        {
            string tmp = str;
            sort(str.begin(), str.end());
            mp[str].push_back(tmp);
        }

        vector<vector<string>> res;
        for (auto &item : mp)
        {
            res.push_back(move(item.second));
        }
        return res;
    }
};

/**
 * @brief Counting Sort
 *
 */

class Solution
{
public:
    string countingSort(string &str)
    {
        int freq[26] = {
            0,
        };

        for (char x : str)
        {
            freq[x - 'a']++;
        }
        string res;
        for (int i = 0; i < 26; i++)
        {
            while (freq[i] > 0)
            {
                res.push_back(i + '0');
                freq[i]--;
            }
        }
        return res;
    }
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> mp;

        for (auto &str : strs)
        {
            string sorted = countingSort(str);
            mp[sorted].push_back(move(str));
        }

        vector<vector<string>> res;
        for (auto &item : mp)
        {
            res.push_back(move(item.second));
        }
        return res;
    }
};