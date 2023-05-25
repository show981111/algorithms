class Solution
{
public:
    int dir[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
    };
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        queue<pair<int, int>> q;
        int M = mat.size();
        int N = mat[0].size();

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (mat[i][j] == 0)
                    q.push({i, j});
            }
        }
        int dis = 0;
        while (!q.empty())
        {
            const int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                pair<int, int> cur = q.front();
                q.pop();
                // mat[cur.first][cur.second] = dis;
                // in this case we don't need this.
                // making it visited at this level is for the first level nodes
                for (int j = 0; j < 4; j++)
                {
                    int nextRow = cur.first + dir[j][0];
                    int nextCol = cur.second + dir[j][1];
                    // if you are checking it later, then you should check it visited
                    // at the same time!
                    if (nextRow >= 0 && nextRow < M && nextCol >= 0 && nextCol < N && mat[nextRow][nextCol] == 1)
                    {
                        q.push({nextRow, nextCol});
                        mat[nextRow][nextCol] = dis - 1;
                        // check it visited, so that it won't pushed twice to queue in the same level
                    }
                }
            }
            dis--;
        }

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (mat[i][j] < 0)
                    mat[i][j] = -mat[i][j];
            }
        }
        return mat;
    }
};