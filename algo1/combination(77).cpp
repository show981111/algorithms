/**
 * @brief
 * BackTracking -> Find recursive form of the problem!
 * Remember the template of genPerms
 *
 */

class Solution
{
public:
    vector<vector<int> > res;
    void genComb(int n, int k, int targetLength, vector<int> &item)
    {
        if (item.size() == targetLength)
        {
            res.push_back(item);
        }
        if (n < k || n <= 0 || k <= 0)
            return;
        item.push_back(n);                         // n is already in the set
        genComb(n - 1, k - 1, targetLength, item); // choose k-1 from 1 ~ n-1
        item.pop_back();                           // pop "n"
        genComb(n - 1, k, targetLength, item);     // choose k items from 1 ~ n
    }
    vector<vector<int> > combine(int n, int k)
    {
        vector<int> item;
        genComb(n, k, k, item);
        return res;
    }
};