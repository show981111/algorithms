class Solution
{
public:
    int binSearch(vector<int> &nums, int start, int end)
    {
        if (start > end)
            return -1;

        int mid = start + (end - start) / 2;
        // if(mid == nums.size()-1) return nums.size();
        if (nums[mid] == mid && nums[mid + 1] != mid + 1)
        {
            return mid + 1;
        }
        else if (mid < nums[mid])
        {
            return binSearch(nums, start, mid - 1);
            // idx == number? so far all good, go right.
            // idx < number? something is missing in left side.
            // idx > number? Impossible. number should be equal or bigger. cuz range is [0~n]
        }
        else if (mid == nums[mid])
            return binSearch(nums, mid + 1, end);
        else
        { // impossible
            return -1;
        }
    }
    int missingNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        // For extreme!
        if (nums.back() != nums.size())
            return nums.size();
        if (nums[0] != 0)
            return 0;
        return binSearch(nums, 0, nums.size() - 1);
    }
};