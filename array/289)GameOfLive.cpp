/**
 *
 * State changes are happening independently(simulataneously).
 * So, each cell refers to current state, not a new state
 * If we update the cell as we traverse, then later cells will refer to a new state :(
 *  -> Need to memorize those information: Aux space introduced to save old states
 *
 * Can we do in O(1)?
 *
 * We are only using 1bits. and each cell is integer which is a 4 bytes. Let's use this space!
 */
class Solution
{
public:
    int dir[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int countLiveNeighbor(vector<vector<int>> &board, int row, int col)
    {
        int num = 0;
        for (int i = 0; i < 8; i++)
        {
            int nextRow = row + dir[i][0];
            int nextCol = col + dir[i][1];

            if (nextRow >= 0 && nextRow < board.size() && nextCol >= 0 && nextCol < board[0].size())
            {
                num += board[nextRow][nextCol];
            }
        }
        return num;
    }
    void gameOfLife(vector<vector<int>> &board)
    {
        vector<vector<int>> newBoard = board;

        for (int r = 0; r < board.size(); r++)
        {
            for (int c = 0; c < board[0].size(); c++)
            {
                int liveNum = countLiveNeighbor(board, r, c);
                if (board[r][c] == 0 && liveNum == 3)
                    newBoard[r][c] = 1;
                else if (board[r][c] == 1)
                {
                    if (liveNum < 2 || liveNum > 3)
                        newBoard[r][c] = 0;
                    else
                        newBoard[r][c] = 1;
                }
            }
        }
        board = newBoard;
    }
};

/**
 * Using a two bit
 */

class Solution
{
public:
    int dir[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int countLiveNeighbor(vector<vector<int>> &board, int row, int col)
    {
        int num = 0;
        for (int i = 0; i < 8; i++)
        {
            int nextRow = row + dir[i][0];
            int nextCol = col + dir[i][1];

            if (nextRow >= 0 && nextRow < board.size() && nextCol >= 0 && nextCol < board[0].size())
            {
                num += board[nextRow][nextCol] % 10;
            }
        }
        return num;
    }

    void gameOfLife(vector<vector<int>> &board)
    {
        for (int r = 0; r < board.size(); r++)
        {
            for (int c = 0; c < board[0].size(); c++)
            {
                int liveNum = countLiveNeighbor(board, r, c);
                int state = board[r][c] % 10;
                if (state == 0 && liveNum == 3)
                    board[r][c] += 10;
                else if (state == 1)
                {
                    if (liveNum < 2 || liveNum > 3)
                        board[r][c] += 0;
                    else
                        board[r][c] += 10;
                }
            }
        }

        for (int r = 0; r < board.size(); r++)
        {
            for (int c = 0; c < board[0].size(); c++)
            {
                // cout << board[r][c] << " ";
                board[r][c] = board[r][c] / 10;
            }
            // cout << endl;
        }
    }
};