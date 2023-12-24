/**
 * Brute force: O(N^2), starting from each index, try if it can travel
 *              => In N size window, in all indices, Accum GAS - Accum Cost >= 0!
 *
 * Order of cost & Gas matters since it is ordered travel => Cannot sort
 *
 * From O(N^2), we somehow need to reuse the previous calculation to compute next iteration.
 * The only difference from previous N window and next N window is, leftmost elem (gets removed) and rightmost elem (gets added)
 *
 * Problem becomes, we are finding an N size window from [0 ~ N 0 ~ N] where all indices has Accum Gas - Accum Cost >= 0!
 *
 */

class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int N = gas.size();
        int rightIter = 0, leftIter = 0;
        int left = 0, right = 0;
        int accumGas = 0;
        int accumCost = 0;

        while (rightIter <= 1 && right < N)
        {
            accumGas += gas[right];
            accumCost += cost[right];
            right = (right + 1) % N;
            if (right == 0)
                rightIter++;
            while (accumCost > accumGas && N * leftIter + left < N * rightIter + right)
            {
                // Can't travel -> Shrink Window
                accumGas -= gas[left];
                accumCost -= cost[left];
                left = (left + 1) % N;
                if (left == 0)
                    leftIter++;
            }

            // left >= right or accumCost <= accumGas
            if (accumCost <= accumGas && (N * (rightIter - leftIter) + right - left == N))
            {
                return left;
            }
        }
        return -1;
    }
};