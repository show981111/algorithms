/*
Why hard..?
Hard to come up with where to start!
Start by dividing the region! and do operation on that each region!
* how to tune offsets?
Run a small example.. see how many steps I should take and what's the start and end (boundary)
    End of first Layer = N - 1 - layer
[1 2 | 3]
[4 5   6]
[7 8   9]
The distance we can go is getting smaller by N - 2*layer - 1
layer is decreasing from the start and end both
ex)
[{1 2 3} 4] Distance = 3
[1 {2} 3 4] Distance = 1
[4  5 6 7]
[7 8   9 10]
*/

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int N = matrix.size();
        for (int layer = 0; layer < N / 2; layer++)
        {
            for (int i = 0; i < N - 2 * layer - 1; i++)
            {                            // length of each partition
                int end = N - 1 - layer; // boundary(end)
                int topLeftTemp = matrix[layer][i + layer];
                matrix[layer][i + layer] = matrix[end - i][layer]; // topLeft <- BottomLeft
                matrix[end - i][layer] = matrix[end][end - i];     // bottomLeft <- BottomRight
                matrix[end][end - i] = matrix[i + layer][end];     // BottomRight <- TopRight
                matrix[i + layer][end] = topLeftTemp;              // TopRight <- topLeft
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