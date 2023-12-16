/**
 * One Idea of getting the minCut.
 *
 * Think it as a graph.
 * At each index i, it is a neighbor with j+1 if S[i:j] is a palindrome (can skip to j+1 in one step!)
 *
 * Now do BFS to get the shortest distance to the target, which is a N!
 * Visited is needed because it is not a tree. Multiple index can be neighbor with the same index. ex) 1 -> 5, 3 -> 5
 */

class Solution
{
public:
    int minCut(string s)
    {
        int N = s.size();
        vector<vector<bool>> memo(N + 1, vector<bool>(N + 1, true));
        unordered_map<int, vector<int>> graph;
        for (int i = 0; i < N; i++)
        {
            graph[i].push_back(i + 1);
        }
        for (int k = 1; k < N; k++)
        {
            for (int row = 1; row < N + 1 - k; row++)
            {
                int col = row + k;
                memo[row][col] = memo[row + 1][col - 1] && s[row - 1] == s[col - 1];
                if (memo[row][col])
                {
                    graph[row - 1].push_back(col);
                }
            }
        }
        vector<bool> visited(s.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int dist = 0;
        while (!q.empty())
        {
            int qSize = q.size();
            for (int i = 0; i < qSize; i++)
            {
                int f = q.front();
                // cout << f << " => ";
                q.pop();
                if (f == N)
                {
                    return dist - 1;
                }
                for (int next : graph[f])
                {
                    // cout << next << " ";
                    if (visited[next] == false)
                    {
                        visited[next] = true;
                        q.push(next);
                    }
                }
                // cout << endl;
            }
            dist++;
        }
        return -1;
    }
};

/**
 * Using DP to count min cut
 *
 * Let T(i) : mincut for S[:i]
 * T(i) = min(T(k-1) + 1) for k S[k:i] is a palindrome so k <= i
 *
 * Initially,
 * T(i,j) : mincur for S[i:j],
 * T(i,j) = min(T(i,k), T(k+1,j)) -> do i need to know from all i? only interested in 0 ~ i
 *                                   Also, one oeprand will be zero if it is a palindrome
 * T(i) = min(1 + T(k+1)) where s[0:k] is a palindrome
 *                        Doesn't make sense since T(i) = mincut for S[0:i], so T(k+1) = mincut for S[0:k+1]
 *                        Should turn this to recurse on T(k) where k <= i since we only know T(k) value for k <= i
 * Thus, T(i) = min(T(k-1) + 1) comes up!
 */
class Solution
{
public:
    int minCut(string s)
    {
        int N = s.size();
        vector<vector<bool>> memo(N + 1, vector<bool>(N + 1, true));
        vector<int> cnt(N + 1, numeric_limits<int>::max());
        // 1-indexed like memo vector
        // cnt[i] = minCut for s[:i-1]
        cnt[0] = 0;
        for (int col = 1; col <= N; ++col)
        {
            for (int row = col; row >= 1; --row)
            {
                if (row != col)
                    memo[row][col] = s[row - 1] == s[col - 1] && memo[row + 1][col - 1];
                if (memo[row][col])
                {
                    cnt[col] = min(cnt[col], 1 + cnt[row - 1]);
                    if (row == 1)
                        cnt[col] = 0;
                }
            }
        }
        return cnt[N] == numeric_limits<int>::max() ? -1 : cnt[N];
    }
};