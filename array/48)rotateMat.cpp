class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int N = matrix.size();
        for (int layer = 0; layer < N / 2; layer++)
        {
            for (int i = layer; i < N - layer - 1; i++)
            {
                int right = matrix[i][N - 1 - layer];
                matrix[i][N - 1 - layer] = matrix[layer][i]; // right <- top
                int bottom = matrix[N - 1 - layer][N - 1 - i];
                matrix[N - 1 - layer][N - 1 - i] = right; // bottom <- right;
                int left = matrix[N - 1 - i][layer];
                matrix[N - 1 - i][layer] = bottom; // left <- bottom
                matrix[layer][i] = left;           // top <- left
            }
        }
    }
};
/**
 * @brief eflection is same as reflection about line y = x and flip...
 * since matrix is 0 X (+)  This coordinate system, we flip with line y = x, and flip by Y axis
 *                 Y
 *                (+)
 * We can prove this by drawing an image
 */

void rotate(vector<vector<int>> &matrix)
{
    int N = matrix.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < N; i++)
        reverse(matrix[i].begin(), matrix[i].end());
}