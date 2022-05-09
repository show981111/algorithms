class Solution
{
public:
    struct Point
    {
        int row;
        int col;
    };

    int dir[4][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}};

    vector<vector<int> > floodFill(vector<vector<int> > &image, int sr, int sc, int newColor)
    {
        queue<Point> q;
        q.push({sr, sc});
        int originalColor = image[sr][sc];
        if (originalColor == newColor)
            return image;
        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            image[cur.row][cur.col] = newColor;

            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.row + dir[i][0];
                int nextCol = cur.col + dir[i][1];
                if (nextRow >= 0 && nextRow < image.size() && nextCol >= 0 && nextCol < image[0].size() && image[nextRow][nextCol] == originalColor)
                {
                    image[nextRow][nextCol] = newColor;
                    q.push({nextRow, nextCol});
                }
            }
        }
        return image;
    }
};