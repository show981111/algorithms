class Solution
{
public:
    /*
    0,1,0,2,1,0,1,3,2,1,2,1

    We can trap the water if the bar forms V shape (Decrease, Increase).
    How do we identify V shapes? First find Decrease sequence, then if we find an increase,
    then it is a V shape. -> Dec stack, We can identify decreasing seuqnce by dec stack, and
    when we face increase, we can pop correspondingly to keep the dec stack.

    When we pop, how do we compute the trapped water?
    Water can be filled from [top()'s index + 1 ~ current -1] = WIDTH,
    Height = Top - Bottom. Top will be the min(next top of the stack, current bar's height) and bottom will be the current top that is getting popped !
    (we can fill water from the lower block to higher block! )
    */
    using Pair = pair<int, int>; // height, idx
    int trap(vector<int> &height)
    {
        stack<Pair> decStack;
        int area = 0;

        for (int i = 0; i < height.size(); i++)
        {
            while (!decStack.empty() && decStack.top().first < height[i])
            {
                Pair t = decStack.top();
                decStack.pop();
                if (!decStack.empty())
                {
                    int l = decStack.top().second;
                    int width = ((i - 1) - (l + 1) + 1);
                    int h = min(height[i], decStack.top().first) - t.first;
                    area += width * h;
                }
            }
            if (!decStack.empty() && decStack.top().first == height[i])
            {
                decStack.top().second = i; // update idx to right most one if the height is the same
            }
            decStack.push({height[i], i});
        }
        return area;
    }
};