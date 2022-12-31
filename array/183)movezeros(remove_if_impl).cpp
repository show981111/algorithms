class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        // Using STL
        // int originalSize = nums.size();
        // nums.erase(remove_if(nums.begin(), nums.end(), [](int &a){
        //     return a == 0;
        // }), nums.end());
        // int zeros = originalSize-nums.size();
        // for(int i = 0; i < zeros; i++)
        //     nums.push_back(0);

        // This is How Remove_if works
        int index = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0)
            {
                nums[index++] = nums[i];
            }
        }
        while (index < nums.size())
        {
            nums[index++] = 0;
        }
    }
};