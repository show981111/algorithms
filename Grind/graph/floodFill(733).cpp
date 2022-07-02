/**
 * @brief BFS
 * We can use a direction array, but in this case we should check visited
 * inside the for loop. Unles, the element can be reinserted to the queue since
 * it is not checked as visted while searching another elem.
 *
 * In this case we are checking the visited when we are popping,
 * and skip the search if we are visited, so we are good.
 */

class Solution
{
public:
    struct Point
    {
        int row;
        int col;
    };

    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
    {
        int originColor = image[sr][sc];
        if (originColor == newColor)
            return image;
        queue<Point> q;
        q.push({sr, sc});
        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            if (cur.row < 0 || cur.row >= image.size() || cur.col < 0 || cur.col >= image[0].size() || image[cur.row][cur.col] != originColor)
                continue;
            image[cur.row][cur.col] = newColor;

            q.push({cur.row + 1, cur.col});
            q.push({cur.row - 1, cur.col});
            q.push({cur.row, cur.col + 1});
            q.push({cur.row, cur.col - 1});
        }

        return image;
    }
};