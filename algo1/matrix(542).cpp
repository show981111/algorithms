class Solution
{
public:
    struct Point
    {
        int row;
        int col;
        int dis;
    };

    vector<vector<int> > updateMatrix(vector<vector<int> > &mat)
    {
        int dir[4][2] = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}};
        queue<Point> q;
        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                if (mat[i][j] == 0)
                    q.push({i, j});
            }
        }

        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            mat[cur.row][cur.col] = cur.dis;
            // cout << cur.row << " " << cur.col << " = " << cur.dis << endl;
            for (int i = 0; i < 4; i++)
            {
                Point next = {cur.row + dir[i][0], cur.col + dir[i][1], cur.dis - 1};
                if (next.row < 0 || next.row >= mat.size() || next.col < 0 || next.col >= mat[0].size() || mat[next.row][next.col] <= 0)
                    continue;
                mat[next.row][next.col] = next.dis;
                q.push(next);
            }
        }

        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                mat[i][j] = -mat[i][j];
            }
        }

        return mat;
    }
};