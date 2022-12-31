/**
 * @brief Rotating Array!
 *
 */

class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        int N = nums.size();
        int start = 0;
        int rotated = 0;
        while (rotated < N)
        {
            int cur = start;
            int realCurVal = nums[start];
            do
            {
                cur = (cur + k) % N;
                swap(nums[cur], realCurVal);
                /**
                 * OR
                 * int temp = nums[cur];
                 * nums[cur] = realCurVal;
                 * realCurVal = temp;
                 */
                rotated++;
            } while (cur != start);
            start++;
        }
    }
};