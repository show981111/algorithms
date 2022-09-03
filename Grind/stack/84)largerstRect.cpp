class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int N = heights.size();

        vector<int> LB(N);
        vector<int> RB(N);

        stack<pair<int, int>> st;

        for (int i = 0; i < N; i++)
        {
            while (!st.empty() && st.top().first >= heights[i])
            { // can go until we meet lower than cur height
                pair<int, int> t = st.top();
                st.pop();
            }
            if (st.empty())
                LB[i] = 0;
            else
                LB[i] = st.top().second + 1;
            st.push({heights[i], i});
        }
        while (!st.empty())
            st.pop();

        for (int i = N - 1; i >= 0; i--)
        {
            while (!st.empty() && st.top().first >= heights[i])
            {
                pair<int, int> t = st.top();
                st.pop();
            }
            if (st.empty())
                RB[i] = N - 1;
            else
                RB[i] = st.top().second - 1;
            st.push({heights[i], i});
        }
        int area = 0;
        for (int i = 0; i < N; i++)
        {
            // cout << i << " " << LB[i] << " " << RB[i] << endl;
            area = max(area, heights[i] * (RB[i] - LB[i] + 1));
        }
        return area;
    }
};

/**
 * @brief Second
 *
 */
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int N = heights.size();
        int area = 0;
        vector<int> LB(N);
        stack<int> st;

        for (int i = 0; i < N; i++)
        {
            while (!st.empty() && heights[st.top()] >= heights[i])
            {
                int topIndex = st.top();
                st.pop();
                area = max(area, heights[topIndex] * (i - 1 - LB[topIndex] + 1));
                // i works as a RB
            }
            if (st.empty())
                LB[i] = 0;
            else
                LB[i] = st.top() + 1;
            st.push(i);
        }
        while (!st.empty())
        {
            int topIndex = st.top();
            st.pop();
            area = max(area, heights[topIndex] * (N - 1 - LB[topIndex] + 1));
        }

        return area;
    }
};

/**
 * @brief Third
 *
 */

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int N = heights.size();
        int area = 0;
        stack<int> st;

        for (int i = 0; i <= N; i++)
        {
            int curHeight = i == N ? 0 : heights[i];
            // when i == N, it pops all left over from stack and calculate area
            while (!st.empty() && heights[st.top()] >= curHeight)
            {
                int topIndex = st.top();
                st.pop();
                int RB = i - 1;
                int LB = !st.empty() ? st.top() + 1 : 0;
                area = max(area, heights[topIndex] * (RB - LB + 1));
            }
            st.push(i);
        }

        return area;
    }
};