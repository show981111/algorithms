#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 *
 *
 */
struct Point
{
    int row;
    int col;
    unordered_set<int> curStamps;
};
bool isIn(int curRow, int curCol, int rowSize, int colSize)
{
    if (curRow >= 1 && curRow <= rowSize && curCol >= 1 && curCol <= colSize)
        return true;
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    int homeRow, homeCol;
    cin >> homeRow >> homeCol;

    int destRow, destCol;
    cin >> destRow >> destCol;

    int MAX_STAMP = 2 * N * M;
    vector<vector<int>> stamps(N + 1, vector<int>(M + 1));
    vector<vector<int>> minStamp(N + 1, vector<int>(M + 1, MAX_STAMP));
    vector<vector<int>> prev(N + 1, vector<int>(M + 1, -1));
    // vector<vector<unordered_set<int>>> minStampState(N + 1, vector<unordered_set<int>>(M + 1));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> stamps[i][j];
        }
    }

    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    queue<Point> q;
    unordered_set<int> curStamps;
    curStamps.insert(stamps[homeRow][homeCol]);
    minStamp[homeRow][homeCol] = 1;
    prev[homeRow][homeCol] = -1;

    q.push({homeRow, homeCol, curStamps});

    int ans = MAX_STAMP;

    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();

        if (minStamp[cur.row][cur.col] < cur.curStamps.size())
        {
            continue;
        }
        if (cur.row == destRow && cur.col == destCol)
        {
            ans = min((int)cur.curStamps.size(), ans);
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int nextRow = cur.row + dir[i][0];
            int nextCol = cur.col + dir[i][1];

            if (isIn(nextRow, nextCol, N, M))
            {
                // cout << nextRow << " " << nextCol << endl;
                bool erase = true;
                if (cur.curStamps.count(stamps[nextRow][nextCol]) > 0) // that stamp is alr in
                {
                    erase = false;
                }
                else
                    cur.curStamps.insert(stamps[nextRow][nextCol]);
                // cout << cur.curStamps.size() << "\n";
                if (minStamp[nextRow][nextCol] >= cur.curStamps.size())
                {
                    if (prev[nextRow][nextCol] == i && minStamp[nextRow][nextCol] == cur.curStamps.size())
                    {
                        continue;
                    }
                    // if (minStamp[nextRow][nextCol] == cur.curStamps.size())
                    // {
                    //     cout << "EQUAL!!!\n";
                    // }
                    prev[nextRow][nextCol] = i;
                    minStamp[nextRow][nextCol] = cur.curStamps.size();
                    q.push({nextRow, nextCol, cur.curStamps});
                    if (erase)
                        cur.curStamps.erase(stamps[nextRow][nextCol]);
                }
            }
        }
    }
    // for (int i = 1; i <= N; i++)
    // {
    //     for (int j = 1; j <= M; j++)
    //     {
    //         cout << minStamp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << minStamp[destRow][destCol];
    return 0;
}