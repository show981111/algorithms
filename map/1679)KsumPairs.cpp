/**
 * Basically Two-sum, but just counting number of pairs!
 * Use MAP!
 * Why not SET? if we use set, cannot count duplicate entries.
 */

class Solution
{
public:
    int maxOperations(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        int pairs = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            int otherPair = k - nums[i];
            if (mp.find(otherPair) != mp.end() && mp[otherPair] > 0)
            {
                pairs++;
                mp[otherPair]--;
                if (mp[otherPair] == 0)
                    mp.erase(otherPair);
            }
            else
            {
                mp[nums[i]]++;
            }
        }

        return pairs;
    }
};