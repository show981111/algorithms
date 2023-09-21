#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * BFS.
 * Use map itself to mark visited -> save mem no need for visited array
 * PLEASE mark visited right before push the item to queue!!!
 * -> prevent pushing the same item again!
 */

struct Point
{
    int row;
    int col;
};
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
void bfs(vector<vector<char>> &map, int r, int c)
{
    queue<Point> q;
    q.push(Point{r, c});
    map[r][c] = 'X';

    while (!q.empty())
    {
        Point f = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextR = f.row + dir[i][0];
            int nextC = f.col + dir[i][1];

            if (nextR >= 0 && nextR < map.size() && nextC >= 0 &&
                nextC < map[0].size() && map[nextR][nextC] == '.')
            {
                map[nextR][nextC] = 'X';
                q.push(Point{nextR, nextC});
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int rowSize, colSize;
    cin >> rowSize >> colSize;

    vector<vector<char>> map(rowSize, vector<char>(colSize));
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; ++j)
        {
            cin >> map[i][j];
        }
    }
    int n = 0;
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; ++j)
        {
            if (map[i][j] == '.')
            {
                bfs(map, i, j);
                n++;
            }
        }
    }
    cout << n << "\n";
}