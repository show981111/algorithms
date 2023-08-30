/**
 * @brief BackTracking
 * Just try every possible cases!
 * => 경우의수 트리를 dfs 하는거라 생각!
 *
 * 이경우, 경우의수 트리는, 퀸이 위치할수 있는 곳 기준으로 생긴다.
 * So, how should we iterate? -> every possible position of queens -> (i,j)
 *
 * Important thing here is, how can we reduce the branch?
 * => One Queen per One Row
 * => WHen we do two for loop, if we go to next row, we assume that we dont place
 * queen in that row => never gonna be an answer! => dont have to iterate all rows
 * => just iterate columns for that row
 */
class Solution
{
public:
    typedef pair<int, int> Point;
    vector<bool> rowCheck; // true : pass / false : no pass
    vector<bool> colCheck;

    bool crossCheck(Point &newQueen, vector<Point> &cur)
    {
        for (Point &p : cur)
        {
            int dx = newQueen.first - p.first;
            int dy = newQueen.second - p.second;
            if (dx == -dy || dx == dy)
            {
                return false;
            }
        }
        return true;
    }

    void addBoard(vector<vector<string>> &res, vector<Point> &cur, int n)
    {
        vector<string> board(n, string(n, '.'));
        for (Point &p : cur)
        {
            board[p.first][p.second] = 'Q';
        }
        res.push_back(move(board));
    }

    void backTrack(vector<vector<string>> &res, int startRow, vector<Point> &cur, int curQueen, int n)
    {
        // base case is when we reached the state we want(end of tree)
        if (curQueen == n)
        {
            addBoard(res, cur, n);
            return;
        }

        // iterate all possible cases
        /**
         * @brief Why use startRow? => since N-queens are combination not a permutation!
         * We cannot distinguish each Queens. Placing [A,B] == [B,A]
         * Thus, we should prevent choosing from previous locations!
         */
        for (int i = startRow; i < n; i++)
        {
            if (!rowCheck[i])
                continue;
            for (int j = 0; j < n; j++)
            {
                Point newQueen = make_pair(i, j);
                if (rowCheck[i] && colCheck[j] && crossCheck(newQueen, cur))
                {
                    cur.push_back(newQueen);
                    rowCheck[i] = false;
                    colCheck[j] = false;
                    backTrack(res, i, cur, curQueen + 1, n);
                    cur.pop_back();
                    rowCheck[i] = true;
                    colCheck[j] = true;
                }
            }
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;
        vector<Point> cur;
        colCheck.resize(n, true);
        rowCheck.resize(n, true);
        backTrack(res, 0, cur, 0, n);
        return res;
    }
};

/**
 * @brief Optimized one
 *
 */

class Solution
{
public:
    typedef pair<int, int> Point;
    vector<bool> rowCheck; // true : pass / false : no pass
    vector<bool> colCheck;

    bool crossCheck(Point &newQueen, vector<Point> &cur)
    {
        for (Point &p : cur)
        {
            int dx = newQueen.first - p.first;
            int dy = newQueen.second - p.second;
            if (dx == -dy || dx == dy)
            {
                return false;
            }
        }
        return true;
    }

    void addBoard(vector<vector<string>> &res, vector<Point> &cur, int n)
    {
        vector<string> board(n, string(n, '.'));
        for (Point &p : cur)
        {
            board[p.first][p.second] = 'Q';
        }
        res.push_back(move(board));
    }

    void backTrack(vector<vector<string>> &res, int startRow, vector<Point> &cur, int curQueen, int n)
    {
        if (curQueen == n)
        {
            addBoard(res, cur, n);
            return;
        }
        // only iterate columns
        for (int j = 0; j < n; j++)
        {
            Point newQueen = make_pair(startRow, j);
            if (colCheck[j] && crossCheck(newQueen, cur))
            {
                cur.push_back(newQueen);
                colCheck[j] = false;
                backTrack(res, startRow + 1, cur, curQueen + 1, n);
                cur.pop_back();
                colCheck[j] = true;
            }
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;
        vector<Point> cur;
        colCheck.resize(n, true);
        rowCheck.resize(n, true);
        backTrack(res, 0, cur, 0, n);
        return res;
    }
};