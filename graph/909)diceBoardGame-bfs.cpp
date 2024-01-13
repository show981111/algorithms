/**
 * Smallest number of moves to reach the destination.
 *  == Shortest distance to dest
 *
 * But, we move with dice not like 2D traversal. It is not intuitive in the beginning to use BFS.
 * However, board is a graph and key point is where we can move at a time.
 * Traditional 2D is 2D directions. With dices, we can move to +1 ~ +6 from current spot.
 *
 * Now, we got the move, just use BFS to reach the destination fastest.
 */
class Solution
{
public:
    typedef pair<int, int> Coord;

    Coord locToCoord(int loc, int n) // square number (0-index) to coordinates
    {
        int row = n - 1 - (loc / n);
        int col;
        if ((n - 1 - row) % 2 == 0)
        {
            // -->
            col = (loc % n);
        }
        else
        {
            // <--
            col = n - 1 - (loc % n);
        }
        return make_pair(row, col);
    }
    void pushLocsInOneMove(queue<int> &q, vector<bool> &visited, int curr, int dest)
    {
        for (int i = 1; i <= 6; i++) // push all spots we can reach with one dice roll
        {
            int next = curr + i;
            if (next > dest)
                return;
            if (visited[next])
                continue;
            visited[next] = true;
            q.push(next);
        }
    }
    int snakesAndLadders(vector<vector<int>> &board)
    {
        int moves = 0;
        int n = board.size();
        int dest = n * n - 1;

        queue<int> q;
        moves++;
        vector<bool> visited(n * n, false);
        pushLocsInOneMove(q, visited, 0, dest);

        while (!q.empty())
        {
            int qSize = q.size();
            for (int i = 0; i < qSize; i++)
            {
                int curr = q.front();
                Coord curLoc = locToCoord(curr, n);
                q.pop();
                if (board[curLoc.first][curLoc.second] > -1)
                {
                    curr = board[curLoc.first][curLoc.second] - 1;
                }
                if (curr == dest)
                    return moves;
                pushLocsInOneMove(q, visited, curr, dest); // push next possible spots
            }
            moves++;
        }

        return -1;
    }
};