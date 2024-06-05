class Solution
{
public:
    void getSubSet(vector<int> &nums, int curXor, int curIndex, int &s)
    {
        if (curIndex == nums.size())
        {
            s += curXor;
            return;
        }
        getSubSet(nums, curXor, curIndex + 1, s);                  // Not including current elem
        getSubSet(nums, curXor ^ nums[curIndex], curIndex + 1, s); // Including current elem
    }
    int subsetXORSum(vector<int> &nums)
    {
        int s = 0;
        getSubSet(nums, 0, 0, s);
        return s;
    }
};
