/**
 * @brief
 * *** The first integer of each row is greater than the last integer of the previous row.
 * Since the 2D matrix is sorted from (0,0) ~ (M,N)
 * We can use BinSeach on 2D matrix
 * rowIndex = 2D_Index / col_length, colIndex = 2D_Index % col_length
 * Time complexity = log(mn) = log(m) + log(n)
 * Space = O(1)
 */

class Solution
{
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        int M = matrix.size();
        int N = matrix[0].size();
        int start = 0;
        int end = M * N - 1;

        while (start <= end) // start can be equal to end so we should use <=, at recursive
        {                    // pattern, we return false at start > end so !
            int mid = start + (end - start) / 2;

            if (matrix[mid / N][mid % N] == target)
                return true;
            else if (matrix[mid / N][mid % N] < target)
                start = mid + 1;
            else
                end = mid - 1;
        }
        return false;
    }
};