/**
 * BForce with Prefix.
 * Target Sum of subarray questions => PREFIX SUM!
 *
 * If there are multiple things that are moving, just be simple and fix one!
 */

class Solution
{
public:
    /*
    2D sliding window?
    Sum to target... -> Prefix sum?
        c j
      0 1 1   0 1 0
    r 1 2 3   1 2 1
    i 0 1 1   1 3 1
    T(r,c,i,j) = (r,c) ~ (i,j) SubMatrixSum
    T(0,0,i,j) - T(0,0,r-1,c-1) - T(0,c,r-1,j) - T(r,0,i,c-1) => Since we want to use prefix,
          c   j                                                   make T() to start from (0,0)
        X X X X
    r   X X X X
        X X X X
    i   X X X X
    T(r,c,i,j)= T(0,0,i,j) - T(0,0,r-1,j) - T(0,0,i,c-1) + T(0,0,r-1,c-1);
    Since there are two coords, need to fix one.
    */
    int getSubMatSum(vector<vector<int>> &matrix, int r, int c, int i, int j)
    {
        // compute submat sum of (r,c) ~ (i,j) submatrix
        int s = matrix[i][j];
        if (r - 1 >= 0)
            s -= matrix[r - 1][j];
        if (c - 1 >= 0)
            s -= matrix[i][c - 1];
        if (r - 1 >= 0 && c - 1 >= 0)
            s += matrix[r - 1][c - 1];
        return s;
    }
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {
        int ROW = matrix.size();
        int COL = matrix[0].size();
        int ans = 0;
        // prefix compute
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (i - 1 >= 0)
                {
                    matrix[i][j] += matrix[i - 1][j];
                }
                if (j - 1 >= 0)
                {
                    matrix[i][j] += matrix[i][j - 1];
                }
                if (i - 1 >= 0 && j - 1 >= 0)
                {
                    matrix[i][j] -= matrix[i - 1][j - 1];
                }
            }
        }

        // Fix (r,c) as a starting point. And compute submat starting from (r,c)
        for (int r = 0; r < ROW; r++)
        {
            for (int c = 0; c < COL; c++)
            {
                // (i,j) is starting pnt
                for (int i = r; i < ROW; i++)
                {
                    for (int j = c; j < COL; j++)
                    {
                        if (getSubMatSum(matrix, r, c, i, j) == target)
                        {
                            ans++;
                        }
                    }
                }
            }
        }

        return ans;
    }
};