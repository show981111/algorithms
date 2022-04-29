class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        vector<int> res;
        res.reserve(nums.size());
        vector<int> arr(10001);
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                arr[nums[i]]++;
            }
            else
            {
                arr[-nums[i]]++;
            }
        }
        int count = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (count == nums.size())
                break;
            while (arr[i] > 0)
            {
                if (arr[i])
                {
                    res.push_back(i * i);
                    arr[i]--;
                    count++;
                }
            }
        }
        return res;
    }
};