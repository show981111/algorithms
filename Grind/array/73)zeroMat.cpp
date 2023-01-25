/*
 * 1) Using O(M+N) Space
 * Have an array col[R], row[C], recored which col and row is zero!
 * 2) Using O(1) Space
 * Use first column and first row as a record..
 * Then, we should be careful to not corrupt the data in first row & col
 * ex) [1, 0]  Setting first row 0, so mat[0][0] = 0, which will erase first column too not only the first row
 *     [1, 1]
 * Thus, we should separatly calculate!
 *
 * How to O(N) -> O(1) space?
 *
 * Major question is
 * can we use the input as a buffer?
 * Can we directly modify an input?
 */

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        bool isFirstRowZero = false;
        bool isFirstColZero = false;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (matrix[i][j] == 0)
                {
                    if (i == 0)
                    {
                        isFirstRowZero = true;
                    }
                    if (j == 0)
                    {
                        isFirstColZero = true;
                    }
                    if (i != 0 && j != 0)
                    {
                        matrix[i][0] = 0; // set row to zero
                        matrix[0][j] = 0; // set col to zero
                    }
                }
            }
        }
        for (int i = 1; i < rowSize; i++)
        {
            if (matrix[i][0] == 0)
            {
                for (int j = 1; j < colSize; j++)
                    matrix[i][j] = 0;
            }
        }

        for (int j = 1; j < colSize; j++)
        {
            if (matrix[0][j] == 0)
            {
                for (int i = 1; i < rowSize; i++)
                    matrix[i][j] = 0;
            }
        }
        if (isFirstRowZero)
        {
            for (int j = 0; j < colSize; j++)
            {
                matrix[0][j] = 0;
            }
        }
        if (isFirstColZero)
        {
            for (int i = 0; i < rowSize; i++)
            {
                matrix[i][0] = 0;
            }
        }
    }
};