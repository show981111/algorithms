/**
 * @brief Using a direction array to traverse matrix spiral!
 *
 */

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> ans;
        int N = matrix.size(), M = matrix[0].size();
        int row = 0, col = 0;
        int dir[4][2] = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // E.  //S.   // W.  // N.
        int dirIndex = 0;
        while (ans.size() != N * M)
        {
            ans.push_back(matrix[row][col]);
            matrix[row][col] = 101;
            int nextRow = row + dir[dirIndex][0];
            int nextCol = col + dir[dirIndex][1];
            if (nextRow < 0 || nextRow >= N || nextCol < 0 || nextCol >= M || matrix[nextRow][nextCol] == 101)
            {
                dirIndex = (dirIndex + 1) % 4;
            }
            row += dir[dirIndex][0];
            col += dir[dirIndex][1];
        }
        return ans;
    }
};