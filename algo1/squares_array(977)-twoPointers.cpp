class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        vector<int> res;

        int start = 0;
        int end = nums.size() - 1;

        while (start <= end)
        {
            if (abs(nums[start]) < abs(nums[end]))
            {
                res.push_back(nums[end] * nums[end]);
                end--;
            }
            else
            {
                res.push_back(nums[start] * nums[start]);
                start++;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};