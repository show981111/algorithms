/**
 * @brief we have an array called step.
 * Step tells us how far should we go in that direction.
 *
 * Except from the beginning, the distance decreases by 1 every time.
 * So we start from the buffer point (0,-1) to keep this rule for
 * all cases!
 * https://leetcode.com/problems/spiral-matrix/discuss/20573/A-concise-C%2B%2B-implementation-based-on-Directions
 */

class Solution
{
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *head)
    {
        if (head == nullptr)
        {
            return vector<vector<int>>();
        }
        vector<vector<int>> ans(m, vector<int>(n, -1));
        int step[2] = {n, m - 1}; // row, col
        int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int curRow = 0, curCol = -1; //!!! important
        ListNode *cur = head;

        while (cur != nullptr)
        {
            for (int dir = 0; dir < 4; dir++)
            {
                int dist = 0;

                while (dist < step[dir % 2] && cur != nullptr)
                {
                    curRow += direction[dir][0];
                    curCol += direction[dir][1];
                    ans[curRow][curCol] = cur->val;
                    cur = cur->next;
                    dist++;
                }
                step[dir % 2]--;
            }
        }
        return ans;
    }
};