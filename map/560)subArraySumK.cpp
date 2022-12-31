class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int prefix = 0;
        unordered_map<int, int> mp;
        int c = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            prefix += nums[i];
            if (prefix == k)
                c++;

            if (mp.find(prefix - k) != mp.end())
            {
                c += mp[prefix - k];
            }

            mp[prefix]++;
        }
        return c;
    }
};