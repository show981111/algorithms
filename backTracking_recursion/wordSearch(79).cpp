/*
TC: O(M*N*4^L) where M is n_rows, N is n_cols and L is the word length. Since branching factor is 4, we do dfs max 4^L

Why we need to backtrack? Can we just leave it as visited?

c a b
a a a

Looking for aab.
We cannot leave it as visited. Need to backtrack for future's visit.
We do visit all possible places from starting point,
but if starting point can actually become a middle point for the answer,
then we miss out that path if we leave it as visited.
Important assumption is that when we do dfs from starting point,
we assume that the word should begin at the starting point which is not true.
(at (0,2) we do dfs from 'a' assume 'a' is the beginning, but it isn't true)
*/

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