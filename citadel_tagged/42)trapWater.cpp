/**
 * Most 2D Area question => MONOTONIC STACK!
 *
 * Push to stack untill ... we get higher height / lower height
 * While popping, compute area -> save needed information in stack!
 *
 */

class Solution
{
public:
    struct Col
    {
        int height;
        int prevHeight;
        int index;
    };
    int trap(vector<int> &height)
    {
        stack<Col> decStack;

        int trap = 0;

        for (int i = 0; i < height.size(); ++i)
        {
            int leftMost = i; // after fill the water, what is the leftmost index of current height?
            // this height started from this index
            // so if hieght is 5 3 3 3, leftMost : 1, 5 5 5 5, leftMost = 0
            while (!decStack.empty() && decStack.top().height < height[i])
            {
                Col &t = decStack.top();
                int canFillHeight = min(t.prevHeight, height[i]);
                // Fill water as much as we can. After we fill water, the height will become
                // canFillHeight.
                trap += (canFillHeight - t.height) * (i - t.index);
                leftMost = decStack.top().index;
                decStack.pop();
            }
            if (!decStack.empty() && decStack.top().height == height[i])
            {
                continue; // keep the left most one.
            }
            else
            { // decStack.empty() || decStack.top().height > height[i]
                int prevHeight = decStack.empty() ? height[i] : decStack.top().height;
                decStack.push(Col{height[i], prevHeight, leftMost});
            }
        }
        return trap;
    }
};