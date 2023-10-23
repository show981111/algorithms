/**
 * Important thing is finding an invariant!
 *
 * Since we need indexDifference, sort will be complicated.
 * Can we solve this without using sorting? -> MAP
 *
 * Since we are looking for |X - nums[i]| >= valueDifference, we only need to know
 * !!max X or min X!! within the index range.
 *
 * Then, how do we know the index range? If I naively iterate,
 * the value that is not in the index range override the min or max.
 *
 * |i - j| >= indexDifference : j <= (i - indexDifference) or (indexDifference + i) <= j
 * All values that are "indexDifference" amount far apart from current i.
 *
 * We only need a pair, so we just store values that are i - indexDifference >= 0.
 * Then at the later part of the array (i >= indexDifference), we can use any values before "i - indexDifference".
 *
 * We only need to !look back!
 * Why?
 * We are iterating forwoard, so if we miss something by not look forward,
 * it will be caught when we are at later part of the array because it will look back.
 *
 * EX) ... 5 ... 10
 * At 5, 5 cannot consider 10 since 10 comes after 5.
 * But at 10, we can consider 5 since 10 is later than 5.
 * Since we only need a pair, it does not matter.
 */

class Solution
{
public:
    vector<int> findIndices(vector<int> &nums, int indexDifference, int valueDifference)
    {
        vector<int> res(2, -1);
        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
        {
            // Invalid since |0 ~ i| < indexDifference, this values will be stored later.
            if (i - indexDifference < 0)
                continue;

            mp[nums[i - indexDifference]] = i - indexDifference;

            bool found = false;

            if (abs(mp.begin()->first - nums[i]) >= valueDifference)
            {
                res[0] = mp.begin()->second;
                res[1] = i;
                found = true;
            }

            if (abs(mp.rbegin()->first - nums[i]) >= valueDifference)
            {
                res[0] = mp.rbegin()->second;
                res[1] = i;
                found = true;
            }

            if (found)
                return res;
        }
        return res;
    }
};