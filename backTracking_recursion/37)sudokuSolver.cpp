/**
 * @brief
 *
 */

// Slower: checking the validity by checking all elements in row, col, or box... =>bottleNeck
class Solution
{
public:
    bool rowChecker(vector<vector<char>> &board, int row)
    {
        bool arr[10] = {
            false,
        };
        for (int j = 0; j < board[row].size(); j++)
        {
            if (board[row][j] == '.')
                continue;
            if (!arr[board[row][j] - '0'])
                arr[board[row][j] - '0'] = true;
            else
                return false;
        }
        return true;
    }
    bool colChecker(vector<vector<char>> &board, int col)
    {
        bool arr[10] = {
            false,
        };
        for (int i = 0; i < board.size(); i++)
        {
            if (board[i][col] == '.')
                continue;
            if (!arr[board[i][col] - '0'])
                arr[board[i][col] - '0'] = true;
            else
                return false;
        }
        return true;
    }
    bool boxChecker(vector<vector<char>> &board, int row, int col)
    {
        bool arr[10] = {
            false,
        };
        int qr = row / 3;
        int qc = col / 3;
        int boxStartRow = qr * 3;
        int boxStartCol = qc * 3;
        for (int i = boxStartRow; i < boxStartRow + 3; i++)
        {
            for (int j = boxStartCol; j < boxStartCol + 3; j++)
            {
                if (board[i][j] == '.')
                    continue;
                if (!arr[board[i][j] - '0'])
                    arr[board[i][j] - '0'] = true;
                else
                    return false;
            }
        }
        return true;
    }

    bool solve(vector<vector<char>> &board, vector<pair<int, int>> &leftOver, int curIndex)
    {
        if (leftOver.size() == curIndex)
        {
            return true;
        }

        pair<int, int> curPos = leftOver[curIndex];
        bool isSolved = false;
        for (int i = 1; i <= 9; i++)
        {
            board[curPos.first][curPos.second] = i + '0';
            if (rowChecker(board, curPos.first) &&
                colChecker(board, curPos.second) &&
                boxChecker(board, curPos.first, curPos.second))
            {
                isSolved = solve(board, leftOver, curIndex + 1);
            }
            if (isSolved)
                return true;
            board[curPos.first][curPos.second] = '.';
        }
        return false;
    }
    void solveSudoku(vector<vector<char>> &board)
    {
        vector<pair<int, int>> leftOver;

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    leftOver.push_back({i, j});
                }
            }
        }

        solve(board, leftOver, 0);
    }
};

// Faster: using a checker array to accelerate the checking!
class Solution
{
public:
    bool rowCheck[9][10] = {
        false,
    }; // in ith row, j is used.
    bool colCheck[9][10] = {
        false,
    }; // in ith col, num j is used
    bool boxCheck[3][3][10] = {
        false,
    }; // in (i,j)th box num k is used
    bool rowChecker(int row, int num)
    {
        return !rowCheck[row][num];
    }
    bool colChecker(int col, int num)
    {
        return !colCheck[col][num];
    }
    bool boxChecker(int row, int col, int num)
    {
        return !boxCheck[row / 3][col / 3][num];
    }

    bool solve(vector<vector<char>> &board, vector<pair<int, int>> &leftOver, int curIndex)
    {
        if (leftOver.size() == curIndex)
        {
            return true;
        }

        pair<int, int> curPos = leftOver[curIndex];
        bool isSolved = false;
        for (int i = 1; i <= 9; i++)
        {
            if (rowChecker(curPos.first, i) &&
                colChecker(curPos.second, i) &&
                boxChecker(curPos.first, curPos.second, i))
            {

                board[curPos.first][curPos.second] = i + '0';
                rowCheck[curPos.first][i] = true;
                colCheck[curPos.second][i] = true;
                boxCheck[curPos.first / 3][curPos.second / 3][i] = true;

                isSolved = solve(board, leftOver, curIndex + 1);

                rowCheck[curPos.first][i] = false;
                colCheck[curPos.second][i] = false;
                boxCheck[curPos.first / 3][curPos.second / 3][i] = false;
            }
            if (isSolved)
                return true;

            board[curPos.first][curPos.second] = '.';
        }
        return false;
    }
    void solveSudoku(vector<vector<char>> &board)
    {
        vector<pair<int, int>> leftOver;

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    leftOver.push_back({i, j});
                }
                else
                {
                    int num = board[i][j] - '0';
                    rowCheck[i][num] = true;
                    colCheck[j][num] = true;
                    boxCheck[i / 3][j / 3][num] = true;
                }
            }
        }

        solve(board, leftOver, 0);
    }
};