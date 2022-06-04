class Solution
{
public:
    int dir[4][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool dfs(vector<vector<char>> &board, const string &target, int curIndex, int row, int col)
    {
        if (curIndex == target.size())
        {
            return true;
        }

        char temp = board[row][col];
        board[row][col] = '-'; // make it visited
        for (int i = 0; i < 4; i++)
        {
            int nextRow = row + dir[i][0];
            int nextCol = col + dir[i][1];
            if (nextRow >= 0 && nextRow < board.size() && nextCol >= 0 && nextCol < board[0].size() && board[nextRow][nextCol] == target[curIndex])
            {
                // nextStep is a valid candidate because of above equality check
                // if it is not equal, do not need to go further. because it is string
                // and string equality is broken right after we found the inequal value
                bool res = dfs(board, target, curIndex + 1, nextRow, nextCol);
                if (res)
                    return res;
            }
        }
        board[row][col] = temp;
        return false;
    }
    bool exist(vector<vector<char>> &board, string word)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                bool res;
                if (board[i][j] == word[0])
                    res = dfs(board, word, 1, i, j);
                if (res)
                    return true;
            }
        }

        return false;
    }
};