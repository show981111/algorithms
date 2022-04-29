class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        int originalSize = nums.size();
        nums.erase(remove_if(nums.begin(), nums.end(), [](int &a)
                             { return a == 0; }),
                   nums.end());
        int zeros = originalSize - nums.size();
        for (int i = 0; i < zeros; i++)
            nums.push_back(0);
    }
};