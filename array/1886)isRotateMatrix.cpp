/**
 * @brief Just compare every element in matrix to target,
 * in case it is rotated!
 *
 * For all elements in Mat, we get possible location of that element in the target,
 * then compare to see if it is rotated or not.
 *
 */

class Solution
{
public:
    bool findRotation(vector<vector<int>> &mat, vector<vector<int>> &target)
    {
        int N = mat.size();
        bool rotated[4] = {true, true, true, true};
        for (int layer = 0; layer < N; layer++)
        {
            for (int i = 0; i < N; i++) // we should run this for All elements in MAT
            {
                int top = target[layer][i];                    // 0 rotated
                int left = target[N - 1 - i][layer];           // 90degree
                int right = target[i][N - 1 - layer];          // 180
                int bottom = target[N - 1 - layer][N - 1 - i]; // 270

                int currentMat = mat[layer][i];
                if (currentMat != top)
                    rotated[0] = false;
                if (currentMat != right)
                    rotated[1] = false;
                if (currentMat != bottom)
                    rotated[2] = false;
                if (currentMat != left)
                    rotated[3] = false;
            }
        }
        return rotated[0] || rotated[1] || rotated[2] || rotated[3];
    }
};