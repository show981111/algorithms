/**
 * Divide & Conquer
 *
 * 1) How to divide?
 * 2) How to merge the results?
 */
class Solution
{
public:
    Node *helper(vector<vector<int>> &grid, int row, int col, int len)
    {
        if (len == 1)
            return new Node(grid[row][col], true);
        if (len == 0)
            return nullptr;
        bool allSame = true;
        int val = grid[row][col];
        for (int r = row; r < row + len; r++)
        {
            for (int c = col; c < col + len; c++)
            {
                if (grid[r][c] != val)
                {
                    allSame = false;
                    break;
                }
            }
            if (!allSame)
                break;
        }

        if (allSame)
            return new Node(val, true);
        else
        {
            int subLength = len / 2;
            Node *topLeft = helper(grid, row, col, subLength);
            Node *topRight = helper(grid, row, col + subLength, subLength);
            Node *bottomLeft = helper(grid, row + subLength, col, subLength);
            Node *bottomRight = helper(grid, row + subLength, col + subLength, subLength);

            Node *node = new Node(val, false, topLeft, topRight, bottomLeft, bottomRight);
            return node;
        }
    }
    Node *construct(vector<vector<int>> &grid)
    {
        return helper(grid, 0, 0, grid.size());
    }
};