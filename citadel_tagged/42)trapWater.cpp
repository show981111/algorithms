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

/**
 * Using two sweeps prefix
 *
 * Important observation:
 * At index i, the amount we can trap is,
 * min(Tallest Block from left, Tallest Block from right)
 * So, How do we know the tallest hieght from both side? => Two sweeps
 */

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int trap = 0;
        vector<int> left(height.size());
        vector<int> right(height.size());
        left[0] = height[0];
        for (int i = 1; i < left.size(); i++)
        {
            left[i] = max(height[i], left[i - 1]);
        }
        cout << endl;
        right.back() = height.back();
        for (int i = right.size() - 2; i >= 0; i--)
        {
            right[i] = max(height[i], right[i + 1]);
        }
        // now compute how much we can trap
        // Cant trap anything on the edge
        for (int i = 1; i < height.size() - 1; i++)
        {
            int waterHeight = min(left[i], right[i]); // max water height we can trap
            if (waterHeight > height[i])
                trap += waterHeight - height[i];
        }

        return trap;
    }
};