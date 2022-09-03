/**
 * @brief Try the example carefully and generalize that process!
 *
 */

class Solution
{
public:
    int trap(vector<int> &height)
    {
        // the amount of water we can trap at the certain point
        // min(maxLeft, maxRight)
        vector<int> maxLeft(height.size());
        vector<int> maxRight(height.size());
        int N = height.size();
        int mL = height[0];
        for (int i = 1; i < N; i++)
        {
            mL = max(mL, height[i - 1]);
            maxLeft[i] = mL;
        }
        int mR = height.back();
        for (int i = N - 2; i >= 0; i--)
        {
            mR = max(height[i + 1], mR);
            maxRight[i] = mR;
        }

        int ans = 0;
        for (int i = 1; i < N - 1; i++)
        {
            int surround = min(maxLeft[i], maxRight[i]);
            if (height[i] < surround)
            {
                ans += surround - height[i];
            }
        }
        return ans;
    }
};