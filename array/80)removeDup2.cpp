/**
 * Same pattern as 26)removeDup
 *
 * Just add one more state (cnt) so that we can count two numbers.
 * Allow swap if cnt <= 2
 */

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int next = 1;
        int prev = nums[0];
        int cnt = 1;

        for (int cur = 1; cur < nums.size(); ++cur)
        {
            if (nums[cur] == prev)
            {
                cnt++;
            }
            else
            {
                cnt = 1;
            }

            if (cnt > 2)
                continue;
            else
            {
                prev = nums[cur];
                swap(nums[cur], nums[next]);
                next++;
            }
        }

        return next;
    }
};