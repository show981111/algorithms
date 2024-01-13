/**
 * N-queens optimized version
 * - At each recursive, consider placing a queen at that row. Not all rows.
 * Since we know that only one queen per row is acceptable, we can just consider at each step, place queen at that row and go to next row.
 *
 * Solutions are distinct in this case because we dont separate each placed queen. (Queen at same positions are the same answer).
 */
class Solution
{
public:
    typedef pair<int, int> Coord;
    bool valid(vector<Coord> &queens, int r, int c)
    {
        for (auto &q : queens)
        {
            if (q.second == c || q.first - r == q.second - c || q.first - r == -(q.second - c))
            {
                return false;
            }
        }
        return true;
    }

    void dfs(int n, int curRow, vector<Coord> &queens, int &cnt)
    {
        if (curRow == n)
        {
            cnt++;
            return;
        }

        for (int c = 0; c < n; ++c)
        {
            if (!valid(queens, curRow, c))
                continue;

            queens.push_back({curRow, c}); // place queen
            dfs(n, curRow + 1, queens, cnt);
            queens.pop_back(); // remove
        }
    }
    int totalNQueens(int n)
    {
        int cnt = 0;
        vector<Coord> queens;

        dfs(n, 0, queens, cnt);
        return cnt;
    }
};