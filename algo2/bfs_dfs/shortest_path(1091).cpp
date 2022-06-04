class Solution
{
public:
    int dir[8][2] = {
        {0, 1},
        {-1, -1},
        {0, -1},
        {-1, 1},
        {1, 0},
        {1, -1},
        {-1, 0},
        {1, 1},
    };
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        if (grid.empty() || grid[0][0] == 1)
            return -1;
        queue<pair<int, int>> q;
        int M = grid.size();
        int N = grid[0].size();
        q.push({0, 0});
        grid[0][0] = 2;
        int length = 1;
        while (!q.empty())
        {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++)
            {
                pair<int, int> cur = q.front();
                if (cur.first == M - 1 && cur.second == N - 1)
                    return length;
                q.pop();
                for (int k = 0; k < 8; k++)
                {
                    int nextX = cur.first + dir[k][0];
                    int nextY = cur.second + dir[k][1];

                    if (nextX >= 0 && nextX < M && nextY >= 0 && nextY < N && grid[nextX][nextY] == 0)
                    {
                        grid[nextX][nextY] = 2;
                        q.push({nextX, nextY});
                    }
                }
            }
            length++;
        }
        return -1;
    }
};