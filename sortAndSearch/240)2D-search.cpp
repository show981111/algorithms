
/**
 * @brief O(N+M)
 * Think which part we can throw away.
 * !!We can start from whereever we want!!
 * How to throw away some portions?
 *
 * Why hard?
 * If I start from top left, don't know how to proceed.
 * If curVal > target, should I go right or down?
 * If I go bottom, might miss the value in current row.
 * If I go right, might miss the value in current column.
 * (Suppose we don't come back to that row or col, if we com back, it is O(MN))
 *
 * -> SO start from TOP RIGHT (Use Property of ascending soted)
 * If curVal > target, Must go left to decrease the value. If we go down, value goes up.
 * If curVal < target, Must go down to increase the value. If we go left, value goes down.
 *
 * TLDR: Find a path that we value goes different order. (One path goes ascending, other path goes descending)
 * SO that we can choose where to go.
 */
class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int curRow = 0, curCol = matrix[0].size() - 1; // start from top right
        // to rule out one col or one row at each move.
        while (curRow >= 0 && curRow < matrix.size() && curCol >= 0 && curCol < matrix[0].size())
        {
            if (matrix[curRow][curCol] == target)
                return true;
            if (target < matrix[curRow][curCol])
            {
                curCol--; // if target is smaller, cannot exist in cur Col. (sorted top to bottom)
            }
            else
            {
                curRow++; // if target is bigger, cannot exist in cur Row
            }
        }
        return false;
    }
};

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        for (int row = 0; row < matrix.size(); row++)
        {
            vector<int>::iterator iter = lower_bound(matrix[row].begin(), matrix[row].end(), target);
            if (iter != matrix[row].end() && *iter == target)
                return true;
        }
        return false;
    }
};