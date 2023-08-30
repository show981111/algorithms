/**
 * @brief Monotonic Queue
 *          -> (O(nlogn) -> O(n) just throw away bigger ones as we iterate!)
 * Use it when we know that we can throw smaller values as we proceed!
 * How to make it ?
 * As we proceed, throw away values that are bigger than current one.
 * cuz we know that we don't need it cuz we can just use the current one.
 *
 * https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/solutions/143726/c-java-python-o-n-using-deque/ 
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