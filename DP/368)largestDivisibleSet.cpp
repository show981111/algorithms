/**
 * Subset questions -> DP or Greedy with sorting or Backtracking
 *
 * First find out what constraints and some characteristic.
 * If we have a solution for N - 1, can we use this for N?
 *
 * characteristic of divisible set
 * -> if N -1 elements make up a divisible set, How can I add one more to it?
 * Depends on the biggest elem. As long as the biggest one can divide the next one we can make it!
 * EX)
 * a < b < c < d < e IS divisible set,
 * ADDING e*x keep the constraints? YES!
 * e % d = 0 e % c = 0, e % b = 0, e % a = 0, so,
 * -> e = dk, e = ck, e = bk, e = ak
 * Now if we add ex, ex % e == 0, ex % d == (e % d) * (x % d) % d == 0 since e % d ==0.
 * Thus, ex can be divided by all other numbers.
 *
 * Using this, we can add element to existing set. => LIS pattern!
 */

class Solution
{
public:
    /*
    Smalles k such that
    k^0, k^1, k^2, k^3 ... ka kb
    k 2k 3k 4k 5k 6k -> 6k % 5k ? No
    k k^2 k

    IF
    a < b < c < d < e IS divisible set,
    ADDING e*x keep the constraints? YES!
    e % d = 0, e = dk
    */
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<int> prev(nums.size(), -1);
        vector<int> maxEndingAt(nums.size(), 1);
        int maxLength = 1;
        int maxNode = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] % nums[j] == 0)
                {
                    if (maxEndingAt[i] < maxEndingAt[j] + 1)
                    {
                        maxEndingAt[i] = maxEndingAt[j] + 1;
                        prev[i] = j;
                    }
                }
            }
            if (maxEndingAt[i] > maxLength)
            {
                maxNode = i;
                maxLength = maxEndingAt[i];
            }
        }

        vector<int> answer;
        while (maxNode != -1)
        {
            answer.push_back(nums[maxNode]);
            maxNode = prev[maxNode];
        }

        return answer;
    }
};