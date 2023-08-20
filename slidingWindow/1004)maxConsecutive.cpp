/**
 * @brief TC: O(N), SC: O(k)
 * queue<int> zeros tracks the location of all zeros, so that we can move start pointer
 * immediately without traversting the array
 */
class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int canFlip = k;
        int maxLength = 0;
        int start = 0, end = 0;
        queue<int> zeros;

        while (end < nums.size())
        {
            if (nums[end] == 0)
            {
                zeros.push(end); // get zero's location
                if (canFlip > 0)
                {
                    canFlip--;
                }
                else
                {
                    // done, we should shrink start so that we can include nums[end]
                    if (!zeros.empty())
                    {
                        start = zeros.front() + 1; // start goes to next farthest zero from end
                        zeros.pop();               // pop that zero cuz "start" passed this zero
                    }
                }
            } // if nums[end] == 1, just increase length
            maxLength = max(maxLength, end - start + 1);
            end++; // increase the end later after we calculate the length! (we only validated until end,
                   // not end + 1, so calculate length before!)
        }
        return maxLength;
    }
};

/**
 * @brief TC: O(2N), SC: O(1)
 * use Two pointer.
 * start pointer just shrinks until it sees the zero!
 * Only difference is, instead of using a extra space, we just iterate until
 * we see the zero!
 *
 * Intuition behind this is, the problem translates to Maximum length subarray with At Most K zeros!
 */
class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int zeroCount = 0;
        int start = 0, end = 0;
        int maxLength = 0;

        while (end < nums.size())
        {
            if (nums[end] == 0)
                zeroCount++;

            if (zeroCount <= k)
            {
                maxLength = max(maxLength, end - start + 1);
            }
            else // we went over the allowable number of zeros, should shrink!
            {    // zeroCount > k, need to get a new start to include nums[end]
                while (nums[start++] != 0)
                {
                } // until start find the zero to take off,
                zeroCount--;
            }
            end++;
        }
        return maxLength;
    }
};