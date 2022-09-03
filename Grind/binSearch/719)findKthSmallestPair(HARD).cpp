/**
 * @brief Finding Pairs with Kth minimum distance!
 * Brute Force
 *  Get all pairs, Sort, return Kth elem => O(N^2logN)
 *
 * Usually do something with pairs can be solved with sort (O(NlogN))
 * 1) Sort
 *      What we know at this point is... maximum distance(nums.back() - nums[0])
 *      Distance of all Pairs <= nums.back()(Max elem) - nums[0](min elem)
 *    Now, how should we know the Kth minimum distance..?
 * 2) Binary Search
 *      Kth distance should be in [0, max distance]
 *      So we do binary search in this range!
 *      Each step, we count pairs which are <= mid distance
 *      if the number of pairs < k
 *          This means mid is too small! so we should go above!
 *          => left = mid + 1
 *      if the number of pairs >= k
 *          This means mid is too big!! so we should go down.
 *          (A) #pairs == k
 *          (B) #pairs > k
 *          even though #pairs == k, we should keep shrinking to go down.
 *          The reason is the mid distance might still be bigger than the actual Kth distance.
 *          EX) [0,1], [1,2], [2,3] and k = 3. and if mid == 2 still gives the pairs.
 *          Thus => Right = mid
 *          Instead we should break when left >= right! not left > right.
 *          if(left == right), cannot guess more...
 * 3)Sliding Window(Counting pairs with distance <= MID) => O(N)
 *      Use catapilar method!
 *      We should use the fact that, if nums[j] - nums[i] = k,
 *      then for all i <= i2 < j2 <= j, nums[j2] - nums[i2] <= k.
 *
 * Finally, complexity should be O(Nlog(max distance))
 */

class Solution
{
public:
    int guess(vector<int> &nums, int left, int right, int k)
    {
        if (left >= right)
        {
            return left;
        }
        int guessDistance = left + (right - left) / 2;
        // cout << left << " " << right << endl;
        int N = nums.size();
        int i = 0, j = 1;
        int cnt = 0;
        while (i < N)
        {
            // cout << i << " " << j << endl;
            if (j < N && nums[j] - nums[i] <= guessDistance)
            {
                j++;
            }
            else
            { // if j reached the end, and it was smaller than guessDistance,
                // after than all i should be distance less than guess. becuase nums[i] <= nums[i + 1]
                cnt += (j - i - 1);
                i++;
                if (i == j)
                    j = i + 1;
            }
        }
        // cout << cnt << endl;

        if (cnt >= k)
        {
            right = guessDistance;
        }
        else
        {
            left = guessDistance + 1;
        }

        return guess(nums, left, right, k);
    }
    int smallestDistancePair(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end());
        return guess(nums, 0, nums.back() - nums[0], k);
    }
};