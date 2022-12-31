/**
 * @brief Using a Map and Union Find
 * to Grouping the nodes!
 *
 */

class Solution
{
public:
    int getParent(vector<int> &g, int x)
    {
        if (x == g[x])
            return x;
        else
            return g[x] = getParent(g, g[x]);
    }
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        unordered_map<string, int> emailToId; // email, id;
        unordered_map<int, vector<string>> idToEmails;
        vector<vector<string>> ans;
        vector<int> group(accounts.size());
        iota(group.begin(), group.end(), 0);

        for (int i = 0; i < accounts.size(); i++)
        {
            int realID = i;
            for (int j = 1; j < accounts[i].size(); j++)
            {
                if (emailToId.find(accounts[i][j]) != emailToId.end())
                {
                    // realID = emailToId[accounts[i][j]];
                    int id = getParent(group, emailToId[accounts[i][j]]);
                    group[id] = i;
                }
                else
                {
                    emailToId[accounts[i][j]] = i;
                }
            }
        }

        // sort emails per ID
        for (auto &item : emailToId)
        {
            idToEmails[getParent(group, item.second)].push_back(item.first);
        }
        // sort each email per ID and push to Answer
        for (auto &item : idToEmails)
        {
            sort(item.second.begin(), item.second.end());
            item.second.insert(item.second.begin(), accounts[item.first][0]);
            ans.push_back(move(item.second));
        }

        return ans;
    }
};