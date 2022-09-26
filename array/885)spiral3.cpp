/**
 * @brief Key point is!
 * When we traverse row, the distance becomes +1,
 * 1, 2, 3, 4, 5 ...
 * Same for col, when we traverse col, the distance we travels +1,
 * 1, 2, 3, 4, 5 ...
 * So we have an array called step and we can use this one!
 *
 * https://leetcode.com/problems/spiral-matrix-iii/discuss/158970/C%2B%2BJavaPython-112233-Steps
 */

class Solution
{
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
    {
        vector<vector<int>> coords;
        int totalNum = rows * cols;
        int step[2] = {1, 1}; // rowStep, colStep
        int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int curRow = rStart;
        int curCol = cStart;
        while (coords.size() < totalNum)
        {
            for (int j = 0; j < 4; j++)
            {
                int dis = 0;
                while (dis < step[j % 2] && coords.size() < totalNum)
                {
                    if (curRow >= 0 && curRow < rows && curCol >= 0 && curCol < cols)
                        coords.push_back({curRow, curCol});
                    curRow += dir[j][0];
                    curCol += dir[j][1];
                    dis++;
                }
                step[j % 2]++;
                if (coords.size() >= totalNum)
                    break;
            }
        }
        return coords;
    }
};