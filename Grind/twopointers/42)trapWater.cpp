/**
 * @brief Trapping Watter
 * https://leetcode.com/problems/trapping-rain-water/submissions/
 *
 * The key point of two pointer is
 * "how to proceed those two pointers"
 * Come up with various examples and try it out!
 *
 * In this case, the height of bars in the middle those not matter
 * (A) if the bar in the middle is taller than bars those pointers refer to
 *      The water will be filled based on two pointers(smaller height)
 * (B) the bars in the middle is shorter
 *      The water will be filled based on two pointers(smaller height)
 *      because those bars will surround the whole container!
 */
class Solution
{
public:
    int trap(vector<int> &height)
    {
        // Two pointer
        int N = height.size();
        int l = 0, r = N - 1;
        int curLeft = height[0];
        int curRight = height[N - 1];
        int ans = 0;
        while (l < r)
        {
            if (curLeft < curRight)
            { // added based on left height
                if (curLeft <= height[l + 1])
                    curLeft = height[l + 1];
                else
                    ans += (curLeft - height[l + 1]);
                l++;
            }
            else
            { // added based on right height (curRight >= curLeft)
                if (curRight <= height[r - 1])
                    curRight = height[r - 1];
                else
                    ans += (curRight - height[r - 1]);
                r--;
            }
        }
        return ans;
    }
};
