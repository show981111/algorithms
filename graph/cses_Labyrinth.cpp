#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <utility>
using namespace std;

/**
 * BFS.
 * Use map itself to mark visited -> save mem no need for visited array
 * PLEASE mark visited right before push the item to queue!!!
 * -> prevent pushing the same item again!
 *
 * Tracing the path of BFS
 * 1) In the map, recored the direction we took instead of visited
 * 2) Then trace this path from dst -> src
 *
 * What if its graph not 2D grid?
 * 1) For each node, record parent. (separate vector)
 *      or in the visited array, record parent's node. -> can serve both visited + parent
 * 2) Follow the parent
 */

struct Point
{
    int row;
    int col;
    // string path;
    bool isValid(int r, int c)
    {
        if (row >= 0 && row < r && col >= 0 && col < c)
        {
            return true;
        }
        return false;
    }
    bool operator==(const Point &b)
    {
        return row == b.row && col == b.col;
    }
};
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

char getLetterDir(int i)
{
    switch (i)
    {
    case 0:
        return 'D';
    case 1:
        return 'U';
    case 2:
        return 'R';
    case 3:
        return 'L';
    default:
        return '!';
    }
}

void tracePath(vector<vector<char>> &map, Point &src, Point dst, string &path)
{
    while (!(dst == src))
    {
        switch (map[dst.row][dst.col])
        {
        case 'U':
            path.push_back('U');
            dst.row += 1;
            break;
        case 'L':
            path.push_back('L');
            dst.col += 1;
            break;
        case 'D':
            path.push_back('D');
            dst.row -= 1;
            break;
        case 'R':
            path.push_back('R');
            dst.col -= 1;
            break;

        default:
            return;
            break;
        }
        // cout << dst.row << " " << dst.col << endl;
    }
    reverse(path.begin(), path.end());
}
string bfs(vector<vector<char>> &map, Point src, Point &dst)
{
    queue<Point> q;
    q.push(src);
    map[src.row][src.col] = 'X';

    while (!q.empty())
    {
        Point f = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Point next{f.row + dir[i][0], f.col + dir[i][1]};

            if (next.isValid(map.size(), map[0].size()) && (map[next.row][next.col] == '.' || map[next.row][next.col] == 'B'))
            {
                map[next.row][next.col] = getLetterDir(i);
                if (next == dst)
                {
                    string path;
                    tracePath(map, src, dst, path);
                    return path;
                }
                q.push(next);
            }
        }
    }
    return "";
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int rowSize, colSize;
    cin >> rowSize >> colSize;
    string path;
    Point src, dst;
    vector<vector<char>> map(rowSize, vector<char>(colSize));
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; ++j)
        {
            cin >> map[i][j];
            if (map[i][j] == 'A')
            {
                src = Point{i, j};
            }
            else if (map[i][j] == 'B')
            {
                dst = Point{i, j};
            }
        }
    }

    path = bfs(map, src, dst);

    if (path == "")
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n"
             << path.size() << "\n"
             << path << "\n";
    }
}