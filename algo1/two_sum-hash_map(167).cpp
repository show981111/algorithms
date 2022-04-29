class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        vector<int> res;
        unordered_map<int, int> nums;

        for (int i = 0; i < numbers.size(); i++)
        {
            if (nums.find(target - numbers[i]) != nums.end())
            {
                res.push_back(nums[target - numbers[i]] + 1);
                res.push_back(i + 1);
                return res;
            }
            else
            {
                nums.insert({numbers[i], i});
            }
        }
        return res;
    }
};