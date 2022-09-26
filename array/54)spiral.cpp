// https://leetcode.com/problems/spiral-matrix/discuss/20599/Super-Simple-and-Easy-to-Understand-Solution

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> ans;
        int N = matrix.size();
        int M = matrix[0].size();
        int rowBegin = 0;
        int rowEnd = N - 1;
        int colBegin = 0;
        int colEnd = M - 1;
        /**
            Consider when there is only two row,
            we should put <= for everything!
        */
        while (rowBegin <= rowEnd && colBegin <= colEnd)
        {
            for (int i = colBegin; i <= colEnd; i++)
            {
                ans.push_back(matrix[rowBegin][i]);
            }
            rowBegin++;
            for (int i = rowBegin; i <= rowEnd; i++)
            {
                ans.push_back(matrix[i][colEnd]);
            }
            colEnd--;
            if (rowBegin <= rowEnd)
            {
                for (int i = colEnd; i >= colBegin; i--)
                {
                    ans.push_back(matrix[rowEnd][i]);
                }
                rowEnd--;
            }
            if (colBegin <= colEnd)
            {
                for (int i = rowEnd; i >= rowBegin; i--)
                {
                    ans.push_back(matrix[i][colBegin]);
                }
                colBegin++;
            }
        }

        return ans;
    }
};