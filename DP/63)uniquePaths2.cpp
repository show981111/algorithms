/**
 * @brief DP counting #ways => divide the case so that there is no overlap!
 * T(n,m) = T(n-1,m) + T(n,m-1) => it should be coming from left or top cannot be both! so no
 * redundant couting in this way!
 *
 * Making it O(1) space
 * Marking in the array itself! -> just need to find a way to distinguish original data from
 * memo data => use negative or something!
 */

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        // T(n,m) = T(n-1,m) + T(n,m-1)
        int N = obstacleGrid.size();
        int M = obstacleGrid[0].size();

        if (obstacleGrid[0][0] != 1)
            obstacleGrid[0][0] = -1;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if ((i == 0 && j == 0) || obstacleGrid[i][j] == 1)
                    continue;
                int fromTop = i - 1 >= 0 && obstacleGrid[i - 1][j] != 1 ? obstacleGrid[i - 1][j] : 0;
                int fromLeft = j - 1 >= 0 && obstacleGrid[i][j - 1] != 1 ? obstacleGrid[i][j - 1] : 0;
                obstacleGrid[i][j] = fromTop + fromLeft;
            }
        }

        return obstacleGrid[N - 1][M - 1] == 1 ? 0 : -obstacleGrid[N - 1][M - 1];
    }
};