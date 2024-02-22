/**
 * Need to group numbers within the range (differences <= k). -> Sorting to see which one are close to each other
 */
class Solution
{
public:
    /*
    [a b c d e f g]
    if g - a <= k, can put anything.
    [a b c d e // f g h i j k l]
    Need to group with closer one 100%.
    If we group with something farther, then somthing closer one will have bigger
    difference with father elems.
    EX) [1,2,3,4, 6, 7], k = 3
    [1,2,3,4] within range.
    If we group (1,3,4) then 2 will have bigger difference with 6 than 4.
    */
    vector<vector<int>> divideArray(vector<int> &nums, int k)
    {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i += 3)
        {
            int rep = nums[i];
            auto bound = upper_bound(nums.begin() + i, nums.end(), rep + k);
            // 1 1 3 3 4 5 7 8 9
            //  cout << i << " " << bound - nums.begin() << " ";
            if (bound - (nums.begin() + i) >= 3)
            {
                ans.push_back({nums[i], nums[i + 1], nums[i + 2]});
            }
            else
            {
                return vector<vector<int>>();
            }
        }
        return ans;
    }

    /**
     * Don't even need upper bound. Since we always push back the closest ones.
     * Just see if i+2 is within the range. Otherwise, impossible
     */
    vector<vector<int>> divideArray(vector<int> &nums, int k)
    {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i += 3)
        {
            if (i + 2 < nums.size() && nums[i + 2] - nums[i] <= k)
            {
                ans.push_back({nums[i], nums[i + 1], nums[i + 2]});
            }
            else
            {
                return vector<vector<int>>();
            }
        }
        return ans;
    }
};