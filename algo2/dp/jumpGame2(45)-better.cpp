/**
 * @brief Record Farthest index it can reach and current step's reachPoint.
 * Time : O(n), Space : O(1)
 *
 */
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int N = nums.size();
        int to = 0; // with current step, we can reach "to"
        int step = 0;
        int farthest = 0; // with "Next step" we can reach to the farthest point

        for (int i = 0; i < N - 1; i++)
        {
            if (i < to) // if i is smaller than to, then still in the same step and updating farthest
            {           // why we use < instead of <= ? : since we update to = max(farthest, i + nums[i]),
                farthest = max(farthest, i + nums[i]);
            }
            else
            {                                    // i > to
                to = max(farthest, i + nums[i]); // if i goes above to, we should update step
                step += 1;                       // and update "to" to the farthest
            }
            if (to >= N - 1)
                return step;
        }
        return step;
    }
};

// Below is using i <= to
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int N = nums.size();
        int to = 0; // with current step, we can reach "to"
        int step = 0;
        int farthest = 0; // with "Next step" we can reach to the farthest point

        for (int i = 0; i < N; i++)
        {
            if (i <= to) // with "step", we can reach "to"
            {
                farthest = max(farthest, i + nums[i]); // within current step, record farthest
            }
            else
            {
                to = farthest;                         // if i goes above to, we should update step and update "to" to farthest
                farthest = max(farthest, i + nums[i]); // update farthest!! since we went above to, we should update fartest from the beginning
                step += 1;                             // update Step
            }
        }
        return step;
    }
};