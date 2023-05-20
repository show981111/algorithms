#include <iterator>

class Solution
{
public:
    long long countPairs(vector<int> &nums, int k)
    {
        // Brute Force -> N^2 by computing all pairs
        unordered_map<int, long long> mp;
        long long count = 0;

        // METHOD 1 O(N*sqrt(K))
        //  max size of mp? -> sqrt(k) b/c maximum number of divisors of k
        //  is sqrt(k) -> maximum number of possible gcd is sqrt(k)
        for (int i = 0; i < nums.size(); i++)
        {
            int key = gcd(nums[i], k);
            counting like Two - sum !for (auto &it : mp)
            {
                long long mul = (long long)it.first * (long long)key;
                if (mul % k == 0)
                {
                    count += it.second; // create pair (nums[i], it.second)
                }
            }
            mp[key]++;
        }

        // METHOD 2
        // split counting and collecting the number!
        //  O(N+K)
        for (int i = 0; i < nums.size(); i++)
        {
            int key = gcd(nums[i], k);
            mp[key]++;
        }

        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            // counting the sqrt case
            if ((long)it->first * (long)it->first % k == 0)
            {
                count += it->second * (it->second - 1) / 2;
            }
            for (auto itt = next(it, 1); itt != mp.end(); ++itt)
            {
                long long mul = (long long)it->first * (long long)itt->first;
                if (mul % k == 0)
                {
                    count += it->second * itt->second;
                }
            }
        }

        return count;
    }
};