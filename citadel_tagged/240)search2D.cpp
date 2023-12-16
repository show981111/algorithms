/**
 * Key is finding a way where we can for sure know we can decide
 * which way we should go.
 *
 * When we can go left & bottom, if we go bottom, value increase. If we go left value decrease => So it is a correct way to traverse
 * When we can go Right & bottom, both ways will increase the value.
 * When we can go Right & Up, Right will increase value, Up will decrease so it will work!
 *
 * From topRight, go left & bottom
 */

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int curRow = 0;
        int curCol = matrix[0].size() - 1;

        while (curRow >= 0 && curRow < matrix.size() && curCol >= 0 && curCol < matrix[0].size())
        {
            if (matrix[curRow][curCol] == target)
                return true;
            else if (matrix[curRow][curCol] > target)
            {
                curCol--;
            }
            else
            {
                curRow++; // go down to increase val
            }
        }
        return false;
    }
};

/**
 * Different direction (from bottom left)
 * When we can go Right & Up, Right will increase value, Up will decrease so it will work!
 */

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int curRow = matrix.size() - 1;
        int curCol = 0;

        while (curRow >= 0 && curRow < matrix.size() && curCol >= 0 && curCol < matrix[0].size())
        {
            if (matrix[curRow][curCol] == target)
                return true;
            else if (matrix[curRow][curCol] > target)
            {
                --curRow; // decrease
            }
            else
            {
                ++curCol; // increase
            }
        }
        return false;
    }
};