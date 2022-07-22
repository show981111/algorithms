/**
 * @brief BFS
 * We are starting a BFS from every rotten orange.
 * The time that is needed to make every orange rotten is
 * the same as the max Depth of this BFS.
 *
 * Thus,
 * 1) put every rotten orange to Queue
 * 2) start BFS and add time when each level is all popped.
 *
 */
class Solution
{
public:
    int dir[4][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int orangesRotting(vector<vector<int>> &grid)
    {
        queue<pair<int, int>> q;
        int rowSize = grid.size();
        int colSize = grid[0].size();
        int freshOrange = 0;
        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (grid[i][j] == 2)
                    q.push({i, j});
                else if (grid[i][j])
                    freshOrange++;
            }
        }
        int time = q.empty() ? 0 : -1; // since starting is all rotten orange
        while (!q.empty())
        {
            int qSize = q.size();

            for (int i = 0; i < qSize; i++)
            {
                pair<int, int> cur = q.front();
                q.pop();

                for (int j = 0; j < 4; j++)
                {
                    int nextRow = cur.first + dir[j][0];
                    int nextCol = cur.second + dir[j][1];
                    if (nextRow >= 0 && nextRow < rowSize && nextCol >= 0 && nextCol < colSize && grid[nextRow][nextCol] == 1)
                    {
                        grid[nextRow][nextCol] = 2;
                        freshOrange--;
                        q.push({nextRow, nextCol});
                    }
                }
            }
            time++;
            // cout << qSize << endl;
        }
        if (freshOrange > 0)
            return -1;
        return time;
    }
};