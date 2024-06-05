class Solution
{
public:
    /*
    How to compute the area of rectangle?
    Width * Height
    Let's do this row by row.
    At each row, record the maximum height from column j.

    When we see height[j], we need an info that what is the
    rectangle we can make. Which means, what is the height, and what is the width.
    Thus, we need an information where does that "height" started.
    Then we can do, height * (current - height.started + 1) to get area.
    We cannot make a rectangle of height h[i], if h[i+1] < h[i].
    Thus, no point saving h[i]. However, we can build a rectangle of height h[i],
    if h[i] > h[i+1]. Thus, use increasing stack to save the heights we can build.
    */
    using Pair = pair<int, int>; // height, starts
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int R = matrix.size();
        int C = matrix[0].size();

        vector<int> heights(C, 0); // save accumualated heights as the row increases.

        int maxArea = 0;
        for (int r = 0; r < R; r++)
        {
            stack<Pair> st;
            // add one extra iteration to pop values from stack and compute area.
            for (int c = 0; c < C + 1; c++)
            {
                int starts = c;
                if (c < C)
                {
                    if (matrix[r][c] == '1')
                        heights[c] += 1;
                    else
                        heights[c] = 0;
                }
                int curHeight = c == C ? 0 : heights[c];
                maxArea = max(maxArea, curHeight);
                while (!st.empty() && st.top().first >= curHeight)
                {
                    starts = st.top().second;
                    int width = ((c - 1) - starts + 1);
                    maxArea = max(maxArea, width * st.top().first);
                    // when popping, we compute area
                    st.pop();
                }
                st.push({curHeight, starts});
            }
        }

        return maxArea;
    }
};

/**
 * Memmory optimizer version.
 * Char can contain 256 distinct numbers.
 * Be careful that char is -128 ~ 127, and unsigned char is 0 ~ 255.
 */
class Solution
{
public:
    using Pair = pair<int, int>; // height, starts
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int R = matrix.size();
        int C = matrix[0].size();

        int maxHeight = 0;
        int maxArea = 0;
        for (int r = 0; r < R; r++)
        {
            stack<Pair> st;
            for (int c = 0; c < C + 1; c++)
            {
                int starts = c;
                int curHeight = 0;
                if (r > 0 && c < C)
                {
                    if (matrix[r][c] == '1')
                        curHeight = 1 + (int)(matrix[r - 1][c] + 128);
                    matrix[r][c] = (char)(curHeight - 128);
                }
                else if (r == 0 && c < C)
                {
                    curHeight = (matrix[r][c] - '0');
                    matrix[r][c] = (char)(curHeight - 128);
                }
                maxHeight = max(maxHeight, curHeight);
                maxArea = max(maxArea, curHeight);
                while (!st.empty() && st.top().first >= curHeight)
                {
                    starts = st.top().second;
                    int width = ((c - 1) - starts + 1);
                    maxArea = max(maxArea, (width * st.top().first));
                    // when popping, we compute area
                    st.pop();
                }
                st.push({curHeight, starts});
            }
        }
        // func fact. Char's range is -128 ~ 127. Unsigned char is 0 ~ 255
        return maxArea;
    }
};
