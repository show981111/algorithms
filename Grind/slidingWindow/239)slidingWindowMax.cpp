/**
 * @brief Sliding Window
 * Sequence => queue
 * push and pop in both end => deque
 *
 * How to keep the potential max elements?
 * What we need
 *  (1) Max elements in sliding window
 *  (2) Potential max elements which could be the max when current max is popped.
 * We do not need a sorted list. we only need the way to keep potential max.
 *  (A) We do not need previous elements smaller than current elements
 *  (B) if current element is smaller than previous one, it might be the potential max
 * ==> Monotonic Sequence
 *
 * Time Complexity
 * O(N)
 * We can create Monotonic Sequence with deque
 * Each element can be pushed to deque max one, popped max one => O(N)
 *
 * (A) If current element is bigger than deque.back()
 *      pop elements from deque until deque.back() >= current elem
 *      Then push back element
 * (B) If current element is smaller than deque.back()
 *      push back element to deque
 *
 */
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int left = 0, right = 0;
        vector<int> ans;
        deque<int> q;

        while (right < nums.size())
        {
            if (!q.empty())
            {
                if (right - left == k && nums[left++] == q.front())
                    q.pop_front(); // if window size is larger than k, shrink
                if (nums[right] <= q.back())
                    q.push_back(nums[right]);
                else
                {
                    while (!q.empty() && nums[right] > q.back())
                        q.pop_back();
                    q.push_back(nums[right]);
                }
            }
            else
            {
                q.push_back(nums[right]);
            }

            if (right - left + 1 == k) // window size is k than push answer ans, move forward
            {
                right++;
                ans.push_back(q.front());
            }
            else
                right++;
        }

        return ans;
    }
};

/**
 * @brief First solution using a sorted "list"
 *
 * we cannot used std::sort for list
 * use list.sort()
 *
 * O(NlogK) because delete and insert take logK for std::list
 * If its vector or deque, it takes O(K) (shifting)
 */
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int left = 0, right = k;
        vector<int> ans;
        list<int> window;

        for (int i = 0; i < k; i++)
        {
            window.push_back(nums[i]);
        }
        window.sort();
        ans.push_back(window.back());
        // O(NlogK) => TLE, O(NK) => TLE
        while (right < nums.size())
        {
            auto deletePos = lower_bound(window.begin(), window.end(), nums[left++]);
            window.erase(deletePos);

            int val = nums[right++];
            auto insertPos = lower_bound(window.begin(), window.end(), val);
            window.insert(insertPos, val);

            ans.push_back(window.back());
        }

        return ans;
    }
};