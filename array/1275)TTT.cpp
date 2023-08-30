class Solution
{
public:
    int rowCheck(vector<vector<int>> board)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][2] == board[i][0])
            {
                return board[i][0];
            }
        }
        return 0;
    }
    int colCheck(vector<vector<int>> board)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == board[1][i] && board[2][i] == board[0][i])
            {
                return board[0][i];
            }
        }
        return 0;
    }
    int diagDownCheck(vector<vector<int>> board)
    {
        int cur = board[0][0];
        for (int i = 0; i < 3; i++)
        {
            if (board[i][i] != cur)
                return 0;
        }
        return cur;
    }
    int diagUpCheck(vector<vector<int>> board)
    {
        int cur = board[2][0];
        for (int i = 0; i < 3; i++)
        {
            if (board[2 - i][i] != cur)
                return 0;
        }
        return cur;
    }
    string tictactoe(vector<vector<int>> &moves)
    {
        vector<vector<int>> board(3, vector<int>(3, 0));

        for (int i = 0; i < moves.size(); i++)
        {
            board[moves[i][0]][moves[i][1]] = i % 2 == 0 ? 1 : -1;
        }
        int winner = rowCheck(board);
        winner += colCheck(board);
        winner += diagDownCheck(board);
        winner += diagUpCheck(board);
        // only one winner exists, can win with multiple checks

        if (winner > 0)
        {
            return "A";
        }
        else if (winner < 0)
        {
            return "B";
        }
        else
            return moves.size() == 9 ? "Draw" : "Pending";
    }
};