class Solution
{
public:
    int dir[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}};
    int getArea(vector<vector<int> > &grid, int row, int col)
    {
        queue<pair<int, int> > q;
        q.push({row, col});
        int area = 1;
        while (!q.empty())
        {
            pair<int, int> cur = q.front();
            q.pop();
            grid[cur.first][cur.second] = -1;
            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.first + dir[i][0];
                int nextCol = cur.second + dir[i][1];

                if (nextRow >= 0 && nextRow < grid.size() && nextCol >= 0 && nextCol < grid[0].size() && grid[nextRow][nextCol] == 1)
                {
                    area++;
                    grid[nextRow][nextCol] = -1;
                    q.push({nextRow, nextCol});
                }
            }
        }
        return area;
    }

    int maxAreaOfIsland(vector<vector<int> > &grid)
    {
        int maxArea = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    int curArea = getArea(grid, i, j);
                    if (maxArea < curArea)
                        maxArea = curArea;
                }
            }
        }
        return maxArea;
    }
};