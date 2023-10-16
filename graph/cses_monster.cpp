#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * https://cses.fi/problemset/task/1194
 *
 * Monster can move any direction at each step every time I move.
 * How can I for sure avoid monster?
 *
 * Since monster can go any direction, all that matters is the distance from monsters.
 * The distance to monster from current cell > steps
 * Which means, if I arrive at cell (4,5) with 3 steps, monster shouldn't be able to come here within 3 steps.
 * Thus, distance from monster to this cell should be 4, 5, or 6 ...
 *
 * Also, we want to know the shortest distance to that cell because we should figure out
 * if that cell is unreachable with that number of steps.
 * => Shortest distance in undirected graph : BFS!
 *
 * Perform 2 BFS for clarity.
 * 1) Get shortest distance from monsters to every possible cells
 * 2) Perform BFS from source to any border cell.
 *
 * Tracing back BFS -> Use visited array (record direction and trace back)
 * If it is not a grid but actual graph, need to store prev cell at each node
 */
struct Point
{
    int row;
    int col;
    bool inBoard(int r, int c)
    {
        return row >= 0 && row < r && col >= 0 && col < c;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<int>> distanceFromMonster(n, vector<int>(m, -1));
    vector<vector<char>> visited(n, vector<char>(m, '.'));
    queue<Point> q;
    Point src;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'M')
            {
                q.push({i, j});
                distanceFromMonster[i][j] = 0;
            }
            else if (grid[i][j] == 'A')
            {
                src = Point{i, j};
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
                {
                    cout << "YES\n";
                    cout << 0;
                    return 0;
                }
            }
        }
    }
    const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    const char dirChar[4] = {'D', 'U', 'R', 'L'};
    int dist = 0;
    while (!q.empty())
    {
        int qSize = q.size();

        for (int i = 0; i < qSize; i++)
        {
            Point f = q.front();
            q.pop();
            distanceFromMonster[f.row][f.col] = dist;
            for (int d = 0; d < 4; d++)
            {
                Point nextPoint{f.row + dir[d][0], f.col + dir[d][1]};
                if (nextPoint.inBoard(n, m) && grid[nextPoint.row][nextPoint.col] != '#' && distanceFromMonster[nextPoint.row][nextPoint.col] == -1)
                {
                    distanceFromMonster[nextPoint.row][nextPoint.col] = dist + 1;
                    q.push(nextPoint);
                }
            }
        }
        dist++;
    }

    // cout << "ckp\n";
    q.push(src);
    Point goal;
    bool foundGoal = false;
    visited[src.row][src.col] = 'A';

    int range = 0;
    while (!q.empty())
    {
        int qSize = q.size();

        for (int i = 0; i < qSize; i++)
        {
            Point f = q.front();
            q.pop();
            // cout << f.col << " " << f.row << endl;
            for (int d = 0; d < 4; d++)
            {
                Point nextPoint{f.row + dir[d][0], f.col + dir[d][1]};
                if (nextPoint.inBoard(n, m) && grid[nextPoint.row][nextPoint.col] != '#' && visited[nextPoint.row][nextPoint.col] == '.' &&
                    (distanceFromMonster[nextPoint.row][nextPoint.col] > range + 1 || distanceFromMonster[nextPoint.row][nextPoint.col] == -1))
                {
                    visited[nextPoint.row][nextPoint.col] = dirChar[d];
                    if (nextPoint.row == 0 || nextPoint.col == 0 || nextPoint.row == n - 1 || nextPoint.col == m - 1)
                    {
                        goal = nextPoint;
                        foundGoal = true;
                        // cout << goal.row << "  " << goal.col << endl;
                        break;
                    }
                    q.push(nextPoint);
                }
            }
            if (foundGoal)
                break;
        }
        // cout << "qSize " << q.size() << " goal? " << foundGoal << "\n";
        if (foundGoal)
            break;
        range++;
    }

    if (foundGoal == false)
    {
        cout << "NO";
        return 0;
    }

    vector<char> path;
    Point cur = goal;
    while (cur.row != src.row || cur.col != src.col)
    {
        char d = visited[cur.row][cur.col];
        path.push_back(d);
        if (d == 'U')
        {
            cur.row += 1; // go down
        }
        else if (d == 'L')
        {
            cur.col += 1;
        }
        else if (d == 'D')
        {
            cur.row -= 1;
        }
        else if (d == 'R')
        {
            cur.col -= 1;
        }
    }
    cout << "YES\n";
    cout << path.size() << "\n";
    for (auto iter = path.rbegin(); iter != path.rend(); ++iter)
    {
        cout << *iter;
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << distanceFromMonster[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << visited[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}