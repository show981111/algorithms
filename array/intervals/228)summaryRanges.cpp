/**
 * Look Ahead.
 * Deal with the last element at the end based on condition.
 *
 */

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        if (nums.empty())
            return vector<string>();

        vector<string> ans;
        string cur = "";
        for (int i = 0; i < nums.size() - 1; i++)
        {
            string w = to_string(nums[i]);
            if (nums[i] + 1 == nums[i + 1])
            {
                if (cur.empty())
                    cur += w;
            }
            else
            {
                // broke
                if (cur.empty())
                {
                    cur = w;
                }
                else
                {
                    cur += "->" + w;
                }
                ans.push_back(cur);
                cur = "";
            }
        }
        if (cur.empty())
            ans.push_back(to_string(nums.back()));
        else
        {
            cur += "->" + to_string(nums.back());
            ans.push_back(cur);
        }
        return ans;
    }
};