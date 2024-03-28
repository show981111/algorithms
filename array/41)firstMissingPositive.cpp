class Solution
{
public:
    /*
    Important observation: Answer should be one between [1,nums.size()+1]
    nums.size() array can only store 1 ~ nums.size().

    How to mark this positive integer is in nums array in place?
    Range of the num doesn't allows us to mark in a bit or something.
    Since negatives are uselss, we can just zero out them. Now we can mark
    numbers with neg sign!
    */
    int firstMissingPositive(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] <= 0)
            { // non-postive numbers are useless
                nums[i] = nums.size() + 2;
            }
        }

        for (int i = 0; i < nums.size(); i++)
        {
            int num = abs(nums[i]) - 1;
            if (num >= 0 && num < nums.size())
            {
                if (nums[num] > 0)          // can be dup nums
                    nums[num] = -nums[num]; // mark nums[i]'s existence
            }
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};

class Solution
{
public:
    /*
    Using a sort.
    */
    int firstMissingPositive(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int smallestPos = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > smallestPos)
                return smallestPos;
            else if (nums[i] == smallestPos)
                ++smallestPos;
        }
        return smallestPos;
    }
};