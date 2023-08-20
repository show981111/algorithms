class Solution
{
public:
    int totalFruit(vector<int> &fruits)
    {
        // max two types of fruit
        // contiguously pick fruits! -> SubArray -> Sliding Window
        // Max Window with At Most 2 numbers
        int start = 0, end = 0;
        int n = fruits.size();
        unordered_map<int, int> mp;
        int maxLeng = 0;

        while (end < n)
        {
            mp[fruits[end]]++;
            if (mp.size() <= 2)
                maxLeng = max(maxLeng, end - start + 1);

            while (mp.size() > 2)
            {
                mp[fruits[start]]--;
                if (mp[fruits[start]] == 0)
                    mp.erase(fruits[start]);
                start++;
            }
            end++;
        }

        return maxLeng;
    }
};