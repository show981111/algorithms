class Solution
{
public:
    vector<int> maxSubsequence(vector<int> &nums, int k)
    {
        // find largest K elements!
        int N = nums.size();
        unordered_map<int, int> mp;
        vector<int> sorted = nums;                          // O(N)
        sort(sorted.begin(), sorted.end(), greater<int>()); // O(NlogN)
        for (int i = 0; i < k; i++)
        {
            mp[sorted[i]]++;
        }
        vector<int> ans;
        for (int i = 0; i < N; i++)
        {
            if (mp.find(nums[i]) != mp.end() && mp[nums[i]] > 0)
            {
                ans.push_back(nums[i]);
                mp[nums[i]]--;
            }
        }

        return ans;
    }
};

/**
 * @brief Simple alternative solution
 *
 */
class Solution
{
public:
    vector<int> maxSubsequence(vector<int> &nums, int k)
    {
        // find largest K elements!
        int N = nums.size();
        vector<int> ans;

        for (int i = 0; i < N; i++)
        {
            if (ans.size() < k)
            {
                ans.push_back(nums[i]);
            }
            else
            {
                // find minimum
                auto loc = min_element(ans.begin(), ans.end());
                // if minimum is smaller than current val
                if (*loc < nums[i])
                {
                    ans.erase(loc);         // evict min
                    ans.push_back(nums[i]); // get current val!
                }
            }
        }

        return ans;
    }
};