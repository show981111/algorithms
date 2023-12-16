/**
 * mark each visited O with a group.
 * And for that group, record if that group is surrounded or not.
 */

class Solution
{
public:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    struct Point
    {
        int row;
        int col;
    };

    bool isIn(vector<vector<char>> &board, const Point &cur)
    {
        return cur.row >= 0 && cur.row < board.size() && cur.col >= 0 && cur.col < board[0].size();
    }

    void bfs(vector<vector<char>> &board, Point cur, unordered_map<char, bool> &escaped, char id)
    {
        queue<Point> q;
        q.push(cur);
        board[cur.row][cur.col] = id;
        escaped[id] = false;

        while (!q.empty())
        {
            Point f = q.front();
            q.pop();

            if (f.row == 0 || f.row == board.size() - 1 || f.col == 0 || f.col == board[0].size() - 1)
            {
                escaped[id] = true;
            }

            for (int i = 0; i < 4; i++)
            {
                Point next;
                next.row = f.row + dir[i][0];
                next.col = f.col + dir[i][1];

                if (isIn(board, next) && board[next.row][next.col] == 'O')
                {
                    board[next.row][next.col] = id;
                    q.push(next);
                }
            }
        }
    }

    void solve(vector<vector<char>> &board)
    {
        unordered_map<char, bool> escaped;
        char id = '0';

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == 'O')
                {
                    bfs(board, Point{i, j}, escaped, id++);
                }
            }
        }

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                // cout << board[i][j] << " ";
                if (board[i][j] != 'X' && escaped.count(board[i][j]) > 0)
                {
                    if (escaped[board[i][j]])
                        board[i][j] = 'O';
                    else
                        board[i][j] = 'X';
                }
            }
            // cout << endl;
        }

        return;
    }
};

/**
 * Since if the 'O' touches the border, then it is not surrounded,
 * we can do DFS from only borders.
 */

class Solution
{
public:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    bool isIn(vector<vector<char>> &board, int curRow, int curCol)
    {
        return curRow >= 0 && curRow < board.size() && curCol >= 0 && curCol < board[0].size();
    }

    void dfs(vector<vector<char>> &board, int curRow, int curCol, vector<vector<bool>> &visited)
    {
        visited[curRow][curCol] = true;

        bool res = false;
        for (int d = 0; d < 4; d++)
        {
            int nextRow = curRow + dir[d][0];
            int nextCol = curCol + dir[d][1];

            if (isIn(board, nextRow, nextCol) && board[nextRow][nextCol] == 'O' && !visited[nextRow][nextCol])
            {
                dfs(board, nextRow, nextCol, visited);
            }
        }
    }
    void solve(vector<vector<char>> &board)
    {
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size()));
        for (int i = 0; i < board.size(); i++)
        {
            if (board[i][0] == 'O' && visited[i][0] == false)
            {
                // cout << i << " " << j << endl;
                dfs(board, i, 0, visited);
            }
            if (board[i].back() == 'O' && visited[i].back() == false)
            {
                // cout << i << " " << j << endl;
                dfs(board, i, board[0].size(), visited);
            }
        }

        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[0][j] == 'O' && visited[0][j] == false)
            {
                // cout << i << " " << j << endl;
                dfs(board, 0, j, visited);
            }
            if (board[board.size() - 1][j] == 'O' && visited[board.size() - 1][j] == false)
            {
                // cout << i << " " << j << endl;
                dfs(board, board.size() - 1, j, visited);
            }
        }

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == 'O' && !visited[i][j])
                {
                    board[i][j] = 'X';
                }
            }
        }

        return;
    }
};