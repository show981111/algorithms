/**
 * @brief
 * 1. search based on first int of each row
 * 2. if target > mat[row][0], target is in mat[row ~ end]
 *          so perform binSearch on that Row, then if target is not found,
 *          go to next binSearch based on Row(mid + 1, end)
 * 3. if target < mat[row][0], target is in mat[start ~ row - 1]
 *          so just go to next binSearch based on Row(start, mid - 1)
 * Time Complexity : O(log(m)log(n));
 * Space : O(1) => Tail Recursion
 * However,
 * *** The first integer of each row is greater than the last integer of the previous row.
 * IF The matrix is not sorted up -> down, we cannot use linear travel O(m + n)
 * BUT in this case, it is sorted...
 * We can use Binary Search on whole matrix!
 */

class Solution
{
public:
    bool binSearchForOneDim(vector<int> &row, int target, int start, int end)
    {
        if (start > end)
            return false;
        int mid = start + (end - start) / 2;
        if (row[mid] == target)
            return true;
        else if (row[mid] > target)
        {
            return binSearchForOneDim(row, target, start, mid - 1);
        }
        else
        {
            return binSearchForOneDim(row, target, mid + 1, end);
        }
    }
    bool binSearchOnRow(vector<vector<int> > &matrix, int target, int startRow, int endRow)
    {
        int midRow = startRow + (endRow - startRow) / 2;
        if (startRow > endRow)
            return false;
        if (matrix[midRow][0] == target)
            return true;
        else if (matrix[midRow][0] < target)
        {
            if (*matrix[midRow].rbegin() < target)
                return binSearchOnRow(matrix, target, midRow + 1, endRow);
            else
            {
                if (binSearchForOneDim(matrix[midRow], target, 0, matrix[midRow].size() - 1))
                    return true;
                else
                    return binSearchOnRow(matrix, target, midRow + 1, endRow);
            }
        }
        else // matrix[midRow][0] > target
        {
            return binSearchOnRow(matrix, target, startRow, midRow - 1);
        }
    }
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        return binSearchOnRow(matrix, target, 0, matrix.size() - 1);
    }
};