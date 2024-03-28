class Solution
{
public:
    /*
    Advance right each time. Record longest length.
    If we went over k, shrink until we are good.
    We don't have to push Left back since that will cause us to reach the k again.
    */
    int maxSubarrayLength(vector<int> &nums, int k)
    {
        unordered_map<int, int> freq;
        int maxLeng = 0;
        int left = 0, right = 0;

        while (right < nums.size())
        {
            // forward right
            int curCnt = ++freq[nums[right]];

            // until the subarray is good, we shrink.
            while (curCnt > k)
            {
                int c = nums[left++];
                freq[c]--;
                if (c == nums[right])
                    break;
            }
            right++;
            maxLeng = max(maxLeng, right - left);
        }
        return maxLeng;
    }
};