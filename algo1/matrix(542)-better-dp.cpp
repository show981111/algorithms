/**
 * @brief
 * Grid problem :
 * We do not need to use Queue all the time. We can update
 * each value while we are traversing the grid.
 * How to update the gird?
 * Forward: i: 0 -> mat.size(), j: 0 -> mat[i].size()
 *          Forward direction updates values from left to right, Top to bottom
 *          At this step, we consider every possibilites where we go ->, V directions
 *          for each box in the grid
 * Backward : i: 0 <- mat.size(), j: 0 <- mat[i].size()
 *          Backward direction updates values from right to left, Bottom to Top
 *          At this tep, we consider every possibilites wehere we go <-, ^ directions
 *          for each box in the grid
 * We can compare Forward and Backward to decide which value to keep
 * By running both directions, we can get the result where we use all 4 directions
 * This is sufficient because in Grid we can move max 4 ways <,>,V,^
 * In this way we can updates values without using queue, using a DP way to update values.
 * => O(1) SPACE COMPLEXITY
 */

class Solution
{
public:
    vector<vector<int> > updateMatrix(vector<vector<int> > &mat)
    {
        int maxLength = mat.size() + mat[0].size() + 1;
        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                if (mat[i][j] != 0)
                {
                    int fromTop = i - 1 >= 0 ? mat[i - 1][j] : maxLength;
                    int fromLeft = j - 1 >= 0 ? mat[i][j - 1] : maxLength;
                    mat[i][j] = min(fromTop, fromLeft) + 1;
                }
            }
        }
        for (int i = mat.size() - 1; i >= 0; i--)
        {
            for (int j = mat[i].size() - 1; j >= 0; j--)
            {
                int fromBottom = i + 1 < mat.size() ? mat[i + 1][j] : maxLength;
                int fromRight = j + 1 < mat[i].size() ? mat[i][j + 1] : maxLength;
                mat[i][j] = min(min(fromBottom, fromRight) + 1, mat[i][j]);
            }
        }
        return mat;
    }
};