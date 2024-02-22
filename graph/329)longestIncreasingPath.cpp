/**
 * Graph + DP.
 *
 * DFS is naturally a recursion.
 * Since we are doing a recursion, we can use a memoization to make it more efficient
 * (prevent it from traversing again and again using Visited)
 *
 * ONE INVARIANT IN DFS:
 *  If we call dfs from (r,c) it traverse all paths from (r,c) and its children
 *  Thus, if we computed something from (r,c) than it should be optimal for (r,c) and its children.
 *  => No need to do dfs again for children of (r,c)
 *
 * T(i,j) = longest increasing path starting from (i,j)
 * T(i,j) = 1 + T(of neighbor)
 */

class Solution
{
public:
    /*
    T(i,j) = longest increasing path ends at (i,j)
    T(i,j) = max(T(i-1,j), T(i,j-1), T(i+1,j), T(i,j+1)) + 1 (if its increasing)
           = 1 (otherwise)
    Problem of Two Way sweeping: The path should get concatenated
    ex) 1 -> 2 -> 3 (3), 3 -> 5 -> 8 (3) => should be total 5, but it only count until 3 so the result is 3.

    -------------

    T(i,j) = longest increasing path starting from (i,j)
    T(i,j) = path_so_far + T(of neighbor)
    */
    int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    // in dist, record the longest increasing path starting from r,c
    // dfs returns the longest path starting from r,c
    int dfs(vector<vector<int>> &matrix, vector<vector<int>> &dists, int r, int c)
    {
        if (dists[r][c] > 0)
        {
            return dists[r][c];
            // lemma: dists[r][c] has the optimal longest distance since
            // if we did dfs on r,c before, it will sweep all routes which means optimal
        }
        int bestDistance = 0;
        for (int d = 0; d < 4; d++)
        {
            int nextR = r + dir[d][0];
            int nextC = c + dir[d][1];

            if (nextR >= matrix.size() || nextR < 0 || nextC >= matrix[0].size() || nextC < 0 || matrix[r][c] >= matrix[nextR][nextC])
                continue;
            bestDistance = max(bestDistance, dfs(matrix, dists, nextR, nextC));
        }
        return dists[r][c] = bestDistance + 1; // (r,c)
    }
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        int R = matrix.size(), C = matrix[0].size();
        vector<vector<int>> dists(matrix.size(), vector<int>(matrix[0].size(), 0));
        int ans = 0;

        // O(V+E) = O(V+4V) = O(V) since we are using a visited array!
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if (dists[i][j] == 0)
                    dfs(matrix, dists, i, j);
                ans = max(ans, dists[i][j]);
            }
        }

        return ans;
    }
};
/*
7 8 9
9 7 6
7 2 3
*/