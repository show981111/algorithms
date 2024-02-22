/**
 * 2D Mtrix Prefix Sum!
 *
 * 1) Compute Prefix per row
 * 2) Then, for each pair of columns (c1,c2), we compute prefix of mat[0:r][c1:c2]
 * 3) Now, mat[r1:r2][c1:c2] = mat[0:r2][c1:c2] - mat[0:r1-1][c1:c2];
 *                              So we are doing a prefix on computed row prefix!
 *
 */

class Solution
{
public:
    /*
    2D sliding window?
    Sum to target... -> Prefix sum?
          c j
        X X X X
    r1  X X X X
    r2  X X X X
        X X X X
    T(r,c,i,j)= (mat[r1][c:j]) + ... + (mat[r2][c:j])
              = RowSum[0:r2] - RowSum[0:r1-1];

                Where RowSum[a:b] = (mat[a][c:j]) + (mat[a+1][c:j]) + .. + (mat[b][c:j])
                AND mat[r][c:j] = prefix[r][j] - prefic[r][c-1] (prefix by row)

                Use Map to save RowSum[0:r1-1] value and do look up for O(N) two-sum computation!
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
        // prefix per row compute
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (j - 1 >= 0)
                {
                    matrix[i][j] += matrix[i][j - 1];
                }
            }
        }

        // Since t
        for (int c1 = 0; c1 < COL; c1++)
        {
            for (int c2 = c1; c2 < COL; c2++)
            {
                // For column (c1, c2), compute all submat within that col
                // submatrix that has c1 and c2 as a side.
                int rowSumPrefix = 0;
                unordered_map<int, int> mp;
                mp[0] = 1;
                for (int r = 0; r < ROW; r++)
                {
                    rowSumPrefix += matrix[r][c2];
                    if (c1 - 1 >= 0)
                        rowSumPrefix -= matrix[r][c1 - 1];
                    // if(rowSumPrefix == target) ans++;
                    // rowSumPrefix - delta = target, delta = rowSumPrefix - target
                    if (mp.count(rowSumPrefix - target) > 0)
                    {
                        ans += mp[rowSumPrefix - target];
                    }
                    mp[rowSumPrefix]++;
                }
            }
        }

        return ans;
    }
};