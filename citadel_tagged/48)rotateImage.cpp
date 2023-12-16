/**
 * Identify which one is fixed and which one is moving.
 * Is col or row fixed?
 * Is col/row moving up/left or down/right?
 */

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        for (int layer = 0; layer < matrix.size() / 2; ++layer)
        {
            for (int i = layer; i < matrix.size() - layer - 1; ++i)
            { // 0 ~ 3 -> 1 ~ 1
                // top left: (layer, fixed,i) ->
                int topLeft = matrix[layer][i];
                // Left Bottom : (matrix.size() - i - 1(move up), layer)
                matrix[layer][i] = matrix[matrix.size() - i - 1][layer];
                // Bottom Right : (matrix.size() - layer - 1 (fixed), matrix.size() - 1 - i (move left))
                matrix[matrix.size() - i - 1][layer] = matrix[matrix.size() - layer - 1][matrix.size() - 1 - i];
                // Top RIght : (i (move down), matrix.size() - layer - 1Fixed)
                matrix[matrix.size() - layer - 1][matrix.size() - 1 - i] = matrix[i][matrix.size() - layer - 1];
                // topLeft
                matrix[i][matrix.size() - layer - 1] = topLeft;
            }
        }
    }
};