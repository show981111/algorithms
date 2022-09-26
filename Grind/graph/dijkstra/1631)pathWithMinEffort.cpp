/**
 * @brief Dijkstra ElogE or V^2
 * Matrix is sparse graph because all vertex has a max 4 edges.
 * Sparse graph has a O(1) Edges.
 * Thus, we should use a heap!s
 *
 * Dijkstra is basically alike Prim, but we have to update distance by
 * new_distnace = d_i + w_j (d_i is the distance to parent node, and w_j is the weight
 * from v[i] ~ v[j]), Then
 * d_j = min(new_distance, d_j) => update distance from src
 * Then put it into pq
 *
 *
 * Why we do not check visited when we visit neighboring nodes?
 *  There could be a better distance from other nodes.
 *  If we set it as visited and put it into PQ, then we are only able to
 *  put it into PQ once! => cannot compare options
 * But if we pop that node first, then it is confirmed to be the shortest distance.
 * There is no way we can get shorter distance later(다른데 거쳐가는게 지금거보다 더 짧아야되는데,
 * 그 말은 얘보다 더 먼저 팝이 됫어야한다는 뜻)
 */

class Solution
{
public:
    int dir[4][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    struct Info
    {
        int row;
        int col;
        int effort;
        Info(int r, int c, int e) : row(r), col(c), effort(e) {}
    };

    class Comp
    {
    public:
        bool operator()(const Info &a, const Info &b)
        {
            return a.effort > b.effort;
        }
    };

    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int row = heights.size();
        int col = heights[0].size();
        vector<vector<int>> minEffort(row, vector<int>(col, INT_MAX));
        priority_queue<Info, vector<Info>, Comp> pq;
        pq.push(Info(0, 0, 0));
        minEffort[0][0] = 0;
        while (!pq.empty())
        {
            Info t = pq.top();
            pq.pop();
            int h = heights[t.row][t.col];
            if (h == -1)  // already visited node... since we do not check visited when we
                continue; // push it to the pq, we need to check here
            // when popped from the pq, min distance is confirmed for src -> this node

            // or we can do
            // if(minEffort[t.row][t.col] <= t.effort)
            //     continue;
            heights[t.row][t.col] = -1;

            for (int i = 0; i < 4; i++)
            {
                int nextRow = t.row + dir[i][0];
                int nextCol = t.col + dir[i][1];
                if (nextRow >= 0 && nextRow < row && nextCol >= 0 && nextCol < col && heights[nextRow][nextCol] != -1)
                {
                    int d = max(minEffort[t.row][t.col], abs(heights[nextRow][nextCol] - h));
                    minEffort[nextRow][nextCol] = min(d, minEffort[nextRow][nextCol]);
                    pq.push(Info(nextRow, nextCol, minEffort[nextRow][nextCol]));
                }
            }
        }

        return minEffort[row - 1][col - 1];
    }
};