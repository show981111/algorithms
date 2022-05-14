/**
 * @brief Bottom-up DP
 *
 */

class Solution
{
public:
    // T(i,j)=min(T(i-1,j-1), T(i-1,j)) + arr[i][j]
    int minimumTotal(vector<vector<int> > &triangle)
    {
        if (triangle.size() == 1)
            return triangle[0][0];
        int minRes = INT_MAX;
        for (int i = 1; i < triangle.size(); i++)
        {
            for (int j = 0; j < triangle[i].size(); j++)
            {
                int topLeft = j - 1 >= 0 ? triangle[i - 1][j - 1] : INT_MAX;
                int topRight = j < triangle[i - 1].size() ? triangle[i - 1][j] : INT_MAX;
                int minVal = min(topLeft, topRight);
                triangle[i][j] += minVal;
                if (i == triangle.size() - 1 && minRes > triangle[i][j])
                    minRes = triangle[i][j];
            }
        }
        return minRes;
    }
};