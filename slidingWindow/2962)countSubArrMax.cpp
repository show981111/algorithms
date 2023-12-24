/**
 * When using a catapilar,
 * move right by one step at a time!
 *
 * Then shrink left when right is sufficient.
 *
 * In this way, we can correctly add up additional counts which is possible by previous steps
 *
 * Question:
 * Let M be the maximum element of array.
 * Count the #subarray that cotains at least K number of M.
 *
 * Thus, DP way is that if we habe a subarray that ends at I that satisfies the condition,
 * we can add any element which is I+1_th element to create an equal amount of subarrays.
 *
 * ex) nums = [1,3,2,3,3], k = 2
 * T(I) = #satisfying subarrays that ends at I_th index
 * [1, 3, 2, 3, 3]
 *  0  0  0  2  4 (= 2(Adding current 3 to prev array) + 2)
 * T(I+1) = T(I) + New subarray that can be made by current elem
 */

class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int k)
    {
        int m = nums[0];
        for (int i = 0; i < nums.size(); i++)
            m = max(m, nums[i]);

        int left = 0;
        int right = 0;
        int cnt = 0;
        long long ans = 0;
        long long prevAns = ans;

        while (right < nums.size())
        {
            long long temp = ans;
            ans += prevAns;

            if (nums[right++] == m)
                cnt++;

            long long curCnt = 0;
            while (left < right && cnt >= k)
            {
                if (nums[left++] == m)
                    cnt--;
                ans++;
            }
            // cout << "right :" << right << " ans: " << ans << endl;
            prevAns = ans - temp;
        }
        // ans += prevAns;
        return ans;
    }
};

/**
 * Another method is just adding LEFT!
 *
 * #satisfying subarray == LEFT because [LEFT-1 ~ RIGHT] is the smallest subarray including arr[RIGHT]
 * So, [LEFT-1 ~ RIGHT], [LEFT-2 ~ RIGHT], [LEFT-3 ~ RIGHT], ... [0 ~ RIGHT] all includes at least K number of M's.
 *     | < --                TOTAL #LEFT                              -- > |
 */

class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int k)
    {
        int m = nums[0];
        for (int i = 0; i < nums.size(); i++)
            m = max(m, nums[i]);

        int left = 0;
        int right = 0;
        int cnt = 0;
        long long ans = 0;

        while (right < nums.size())
        {
            if (nums[right++] == m)
                cnt++;

            long long curCnt = 0;
            while (left < right && cnt >= k)
            {
                if (nums[left++] == m)
                    cnt--;
            }
            ans += left;
        }
        return ans;
    }
};