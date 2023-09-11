/**
 * @brief Sliding Window + Prefix sum + Priority Queue
 *
 * Find Shortest subarray that sums up at least K.
 *
 * The loophole is, element can be negative.
 * So, when we shrink the window, since excluding negative can increase the
 * sum, we cannot just stop as soon as curSum < k.
 * Even though curSum < k now, we can push start further and if we exclude couple
 * negative values, we can make a shorter array
 * ex) [1,-4,1,2,3], k = 3 When end is at the end, curSum = 3. if we exclude 1 at the 1st index,
 * curSum = 2, but we can further exclude -4 and get 6!
 *
 * When we have a subarray that sums at least k, how can we cut off meaningless prefix?
 * prefix -> prefix sum(running sum)
 * We can get Sum[i:j] = accum_sum[i] - accum_sum[j-1] (accum_sum[i] means sum[0:i])
 *
 * I wish I can somehow know that which prefix to exclude..
 * We want to start from subtracting [small] prefix -> to cut off the part that does not contribute
 * to K. Then.. how I do this? -> Sort prefix!
 * Starting from small prefix, subtract them until there is no prefix left that makes curSum - prefix >= k.
 * Then, we can get smallest subarray for that "end"
 *
 * We don't need to re_push the element back to pq, because end is getting bigger, so we know
 * that when we popped that elem, the distance should be the shortest.
 *
 * Thus, TC O(nlogn), SC O(N)
 */

class Solution
{
public:
    typedef long long ll;

    struct Info
    {
        ll prefix;
        int index;
    };
    class Comp
    {
    public:
        bool operator()(Info &a, Info &b)
        {
            return a.prefix > b.prefix;
        }
    };
    int shortestSubarray(vector<int> &nums, int k)
    {
        int start = 0, end = 0;
        ll curSum = 0;
        int minLength = nums.size() + 1;
        // how to cut off meaningless prefix?
        priority_queue<Info, vector<Info>, Comp> pq;

        while (end < nums.size())
        {
            curSum += nums[end];
            Info info;
            info.prefix = curSum;
            info.index = end;
            pq.push(info);

            if (curSum >= k)
                minLength = min(minLength, end - start + 1);
            while (!pq.empty() && curSum - pq.top().prefix >= k)
            {
                if (start <= pq.top().index + 1)
                {
                    start = pq.top().index + 1;
                    minLength = min(minLength, end - start + 1);
                }
                pq.pop();
            }

            end++;
        }

        return minLength == nums.size() + 1 ? -1 : minLength;
    }
};

/**
 * @brief MONOTONIC DEQUE
 *
 */
class Solution
{
public:
    typedef long long ll;
    int shortestSubarray(vector<int> &nums, int k)
    {
        int end = 0;
        ll curSum = 0;
        int minLength = nums.size() + 1;

        deque<pair<ll, int>> prevSums; // accum sum , index

        while (end < nums.size())
        {
            curSum += nums[end];
            if (curSum >= k)
                minLength = min(minLength, end + 1); // 0 ~ end (curSum accums from 0)

            // from the farthest, check if something allows us to make a subarray
            while (prevSums.size() > 0 && curSum - prevSums.front().first >= k)
            {
                // we can make smaller subArray!
                // prefix sum. s[j] - s[i] = s[i+1:j]
                minLength = min(minLength, end - (prevSums.front().second + 1) + 1);
                prevSums.pop_front();
                // we are safe to pop this. For this element, current one will make the shortest array. if we go further, the length will incrase!
            }
            // we keep deque increasing, cuz we need to try smallest value first when we trying to make a subarray! -> if we try from bigger one, then fail -> we might have smaller values we haven't tried(can't break while) + cannot just throw away that big value cuz we might need for the future cuz in future if the curSum gets bigger, bigger prefix might works. But for smallest one, if it makes a subarray with at least K, current index will make shortest length -> we can throw away -> O(N)! -> that is why we want to try shorter one first!

            // we can ignore any larger vaules than current one.
            // those can be ignored because we can use this one to make a shorter array!
            while (prevSums.size() > 0 && curSum <= prevSums.back().first)
            {
                prevSums.pop_back();
            }
            prevSums.push_back({curSum, end});
            end++;
        }

        return minLength == nums.size() + 1 ? -1 : minLength;
    }
};