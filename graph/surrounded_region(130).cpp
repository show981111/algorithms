// Memory : O(1) inplace mark, Time : O(mn)

class Solution
{
public:
    int dir[4][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}};
    bool isInside(int row, int col, int rowSize, int colSize)
    {
        if (row < 0 || row >= rowSize || col < 0 || col >= colSize)
            return false;
        return true;
    }

    void dfs(vector<vector<char> > &board, int row, int col)
    {
        board[row][col] = '-';
        for (int i = 0; i < 4; i++)
        {
            int nextRow = row + dir[i][0];
            int nextCol = col + dir[i][1];
            if (isInside(nextRow, nextCol, board.size(), board[0].size()) && board[nextRow][nextCol] == 'O')
            {
                board[nextRow][nextCol] = '-';
                dfs(board, nextRow, nextCol);
            }
        }
    }

    void solve(vector<vector<char> > &board)
    {
        int r = 0;
        for (int i = 0; i < 2; i++)
        { // first and last row
            for (int j = 0; j < board[r].size(); j++)
            {
                if (board[r][j] == 'O')
                {
                    dfs(board, r, j);
                }
            }
            r += board.size() - 1;
        }
        int c = 0;
        for (int j = 0; j < 2; j++)
        { // first and last col
            for (int i = 0; i < board.size(); i++)
            {
                if (board[i][c] == 'O')
                {
                    dfs(board, i, c);
                }
            }
            c += board[0].size() - 1;
        }
        // flip O to X if it is not visted by dfs
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }
                else if (board[i][j] == '-')
                {
                    board[i][j] = 'O';
                }
            }
        }
    }
};