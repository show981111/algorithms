/**
 * @brief Sliding Window
 * Just start from Exclusive! [L, R)
 * L = 0, R = 0; cur = INITIAL VALUE
 * While(L < SIZE && R < SIZE){
 *      if(something)
 *          cur += nums[R++];
 *      else
 *          cur -= nums[L++];
 *     ## Key point here is when R == nums.size()
 *     ## Is there a potential answer cases? (since exclusive!)
 *     Usual pattern is, for each 'R', count or loop every possible
 *     answer cases by shrinking window. Then, go to next step(R++, enlarge window)
 *     while(condition)
 *         cur -= nums[L++];
 * }
 *
 */

class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        int count = 0;
        int left = 0, right = 0;
        unsigned int curMul = 1;
        // Exclusive [left, right)
        while (left < nums.size() && right < nums.size())
        {
            curMul *= nums[right++];

            while (left < right && curMul >= k)
            {
                curMul /= nums[left++];
            }
            count += right - left;
        }

        return count;
    }
};

// 1 2 3 4 5 , ws = 3, N - ws = 3
//

// FOR LOOP
class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        int count = 0;
        int left = 0;
        unsigned int curMul = 1;
        //[left, right] Inclusive!
        for (int right = 0; right < nums.size(); right++)
        {
            if (nums[right] >= k)
            {
                left = right + 1;
                curMul = 1;
                continue;
            }
            curMul *= nums[right];

            while (curMul >= k && left <= right)
            {
                curMul /= nums[left++];
            }
            count += right - left + 1;
        }
        return count;
    }
};

// 1 2 3 4 5 , ws = 3, N - ws = 3
//