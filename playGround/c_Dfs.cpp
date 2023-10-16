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
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(vector<vector<int>> &stamps, vector<vector<int>> &minStamp, vector<vector<bool>> &visited, unordered_set<int> &curStamps, int N, int M, int curRow, int curCol, int destRow, int destCol)
{
    if (curStamps.size() > minStamp[curRow][curCol])
    {
        return;
    }
    if (destRow == curRow && destCol == curCol)
    {
        return;
    }
    visited[curRow][curCol] = true;

    for (int i = 0; i < 4; i++)
    {
        int nextRow = curRow + dir[i][0];
        int nextCol = curCol + dir[i][1];

        if (!isIn(nextRow, nextCol, N, M) || visited[nextRow][nextCol])
            continue;

        bool erase = true;
        if (curStamps.count(stamps[nextRow][nextCol]) > 0) // that stamp is alr in
        {
            erase = false;
        }
        else
            curStamps.insert(stamps[nextRow][nextCol]);

        if (minStamp[nextRow][nextCol] >= curStamps.size())
        {
            minStamp[nextRow][nextCol] = curStamps.size();
            dfs(stamps, minStamp, visited, curStamps, N, M, nextRow, nextCol, destRow, destCol);
        }
        if (erase)
        {
            curStamps.erase(stamps[nextRow][nextCol]);
        }
    }

    visited[curRow][curCol] = false;
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
    // vector<vector<int>> prev(N + 1, vector<int>(M + 1, -1));
    vector<vector<bool>> visited(N + 1, vector<bool>(M + 1, false));
    // vector<vector<unordered_set<int>>> minStampState(N + 1, vector<unordered_set<int>>(M + 1));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> stamps[i][j];
        }
    }

    queue<Point> q;
    unordered_set<int> curStamps;
    curStamps.insert(stamps[homeRow][homeCol]);
    minStamp[homeRow][homeCol] = 1;
    dfs(stamps, minStamp, visited, curStamps, N, M, homeRow, homeCol, destRow, destCol);

    cout << minStamp[destRow][destCol];
    return 0;
}