/**
 * Look back VS Look Forward
 *
 * Look Back: Save previous value, compute based on prev value
 * Look Forward: Compute future value, compute something based on future val
 *
 * Difference with 221)maxSquare.
 *
 * We cannot discard the height when width went over the height since it is a rectangle.
 * Then when can we discard the height?
 *     When we meet the lower height! -> Cannot build a rectangle with that bigger height anymore!
 *     Then... Should I compute everytime col increases with previous heights? -> O(N) for each row
 *     => NO!! Width can be computed just by col - prevHeight.index + 1. Just compute once when we pop that value!
 *     Since as col increases, the rectangle we can build with the height increases. Thus, the area would be the biggest when we pop it!
 */

class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
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
                    maxArea = max(maxArea, h.back().first * (col - h.back().second));
                    h.pop_back();
                }
                h.push_back({mat[row][col], from});
            }
        }
        return maxArea;
    }
};