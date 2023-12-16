/**
 * Computing max Area of histogram when the heights were given.
 *
 * Brute force would be at each index, just compute that size of window. (if height[i] = 3, see if height[i:i+3] >= 3)
 * Will take O(N^2)... how to do better
 *
 * What I know. If the lower height comes in, I cannot make a square with that bigger height. EX) 3 3 1 1 => can't make square with 3
 *              If the bigger height comes in, I can make a squre with current lower height. However, it might be possible to build a square using
 *                                              the bigger height in the future EX) 5 5 7 7 (Still can build 5 height square in the future, but can get 7 squre too!)
 *
 * So, we don't need all height informations if we get lower height column => Monotonic Stack?
 * We only need to save possible heights that can build a square (should be an increasing sequence, if there is lower one in the middle, previous should be abandoned).
 *
 * As we go along, if the width is larger than minHeight, then we can build a square with that minHeight. => Now this height is useless since we already built a square
 *                                                                                                           and we went far enough from that minHeight to discard this
 *                                                                                                        => Need to remove this height => DEQUE! (pop_front)
 *                                                                                                        => Now what is next minHeight? -> Monotonic Stack! (next bottom elem)
 *                                                                                                        => now try building a square with this height!
 *
 * If width is smaller than minHeight, we can at least build a square with WIDTH. But dont discard minHeight since we can build a square with minHeight in the future!
 *
 *
 */

class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        vector<vector<int>> mat(matrix.size(), vector<int>(matrix[0].size()));
        for (int col = 0; col < matrix[0].size(); ++col)
        {
            for (int row = 0; row < matrix.size(); ++row)
            {
                mat[row][col] = matrix[row][col] - '0';
                if (row > 0)
                {
                    if (matrix[row][col] == '1' && matrix[row - 1][col] > '0')
                    {
                        mat[row][col] = mat[row - 1][col] + 1;
                    }
                }
            }
        }

        int maxArea = 0;
        for (int row = 0; row < mat.size(); ++row)
        {
            // int cnt = 0;
            deque<pair<int, int>> h; // minHeight, index

            for (int col = 0; col < mat[row].size(); ++col)
            {
                if (mat[row][col] > 0)
                {
                    int from = col;
                    while (!h.empty() && h.back().first > mat[row][col])
                    {
                        from = h.back().second; // Since this height is bigger, we can still build a squre. So take this index!
                        h.pop_back();
                    }
                    h.push_back({mat[row][col], from});
                }
                else
                {
                    h.clear();
                }

                if (h.size() > 0)
                {
                    int width = col - h.front().second + 1;
                    if (width <= h.front().first)
                    {
                        maxArea = max(maxArea, width * width);
                    }
                    while (h.size() > 0 && width >= h.front().first)
                    {
                        maxArea = max(maxArea, h.front().first * h.front().first);
                        h.pop_front();
                        if (h.size() > 0)
                            width = h.back().second - h.front().second + 1;
                    }
                }
            }
        }
        return maxArea;
    }
};

/**
 * Use maxRectangle
 *
 * Key point is, the only point we need to calculate is when we faced a smaller height
 * since we cannot build a square with that higher height anymore.
 * Since the width is the biggest at this point, we can just compute while popping from the stack!
 *
 */

class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        vector<vector<int>> mat(matrix.size(), vector<int>(matrix[0].size()));
        for (int col = 0; col < matrix[0].size(); ++col)
        {
            for (int row = 0; row < matrix.size(); ++row)
            {
                mat[row][col] = matrix[row][col] - '0';
                if (row > 0)
                {
                    if (matrix[row][col] == '1' && matrix[row - 1][col] > '0')
                    {
                        mat[row][col] = mat[row - 1][col] + 1;
                    }
                }
            }
        }

        int maxArea = 0;
        for (int row = 0; row < mat.size(); ++row)
        {
            // int cnt = 0;
            deque<pair<int, int>> h; // minHeight, index
            mat[row].push_back(0);
            for (int col = 0; col < mat[row].size(); ++col)
            {
                int from = col;
                while (!h.empty() && h.back().first > mat[row][col])
                {
                    from = h.back().second;
                    int side = min(h.back().first, col - h.back().second);
                    maxArea = max(maxArea, side * side);
                    h.pop_back();
                }
                h.push_back({mat[row][col], from});
            }
        }
        return maxArea;
    }
};