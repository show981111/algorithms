/**
 * We have to update the maximum value per window!
 *
 * unordered_map is not sufficient cuz we dont know the ordering
 * Let's use ordered_map!
 *
 * TC: O(nlogn)
 */

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int start = 0;
        int end = 0;
        map<int, int> cnt;

        vector<int> res;

        while (end < (int)nums.size())
        {
            while (end - start + 1 <= k)
            {
                cnt[nums[end++]]++;
            }
            // cout << start << " " << end << endl;
            // end - start + 1 ==k
            res.push_back(cnt.rbegin()->first);

            int startVal = nums[start++];
            cnt[startVal]--;
            if (cnt[startVal] == 0)
                cnt.erase(startVal);
        }

        return res;
    }
};

/**
 * We only need a big value.
 *
 * 1) If we get a bigger value within the window, all previous smaller values are useless
 * -> Just throw away
 *
 * 2) If we get a smaller value within the window, this might be a max value for next window.
 * Since this value comes later in the array.
 *
 * => Feels like monotonic stack!
 *
 * TC: O(n) all elems comes to deque max once.
 */

class Solution
{
public:
    struct Val
    {
        int val;
        int index;
    };
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int start = 0;
        int end = 0;
        deque<Val> dec;

        vector<int> res;

        while (end < (int)nums.size())
        {
            while (end - start + 1 <= k)
            {
                int val = nums[end];
                while (!dec.empty() && dec.back().val < val)
                {
                    dec.pop_back(); // pop all smaller values
                }
                dec.push_back({val, end});
                end++;
            }
            // end - start + 1  > k
            res.push_back(dec.front().val); // Since decresing deque, the bottom one is the biggest

            // shift window
            if (dec.front().index == start)
            {
                dec.pop_front();
            }
            start++;
        }

        return res;
    }
};