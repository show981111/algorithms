/*
Better BFS.
Put every rotten oranges first. then run BFS
So it is like starting BFS at the multiple position
Closer point gets first so do not have to worry about the possibility of shorter path
from another starting point.

#Path Distance
1) Keep track of distance using a struct. Saving distance from previous one,
and add one to it.

2) Check the size of queue at first, iterate the amount of size. Then update distance += 1,
so it is like adding a distance everytime it goes above the level.
*/

class Solution
{
public:
    struct Point
    {
        int row;
        int col;
        int dis;
    };
    int dir[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}};
    int orangesRotting(vector<vector<int> > &grid)
    {
        queue<Point> q;
        int totalOranges = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 0)
                    continue;

                if (grid[i][j] == 2)
                {
                    q.push({i, j, 0});
                }
                totalOranges++;
            }
        } // put every rotten oragnes in

        int maximumNegativeLength = 0;

        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            grid[cur.row][cur.col] = cur.dis;
            if (cur.dis < maximumNegativeLength)
                maximumNegativeLength = cur.dis;

            totalOranges--;

            for (int i = 0; i < 4; i++)
            {
                int nextRow = cur.row + dir[i][0];
                int nextCol = cur.col + dir[i][1];
                if (nextRow >= 0 && nextRow < grid.size() && nextCol >= 0 && nextCol < grid[0].size() && grid[nextRow][nextCol] == 1)
                {
                    grid[nextRow][nextCol] = cur.dis - 1;
                    q.push({nextRow, nextCol, cur.dis - 1});
                }
            }
        }

        if (totalOranges == 0)
            return -maximumNegativeLength;
        else
            return -1;
    }
};