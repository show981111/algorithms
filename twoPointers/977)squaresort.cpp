/**
 * Using already ordered array, use two pointers to push back the bigger square element(compare neg number and pos number)
 * Push smaller ones first
 */

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        vector<int> ans;
        int n = nums.size();
        int neg = -1, pos = -1;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < 0)
                neg = i;
            else
            {
                pos = i;
                break;
            }
        }
        while (ans.size() < n)
        {
            if (neg >= 0 && pos >= 0 && pos < n)
            {
                if (-nums[neg] > nums[pos])
                {
                    ans.push_back(nums[pos] * nums[pos]);
                    pos++;
                }
                else
                {
                    ans.push_back(nums[neg] * nums[neg]);
                    neg--;
                }
            }
            else if (neg >= 0)
            {
                ans.push_back(nums[neg] * nums[neg]);
                neg--;
            }
            else
            {
                ans.push_back(nums[pos] * nums[pos]);
                pos++;
            }
        }
        return ans;
    }
};

/**
 * Different approach of 2 pointers.
 * Push bigger ones first
 */

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ans(n);
        int l = 0, r = nums.size() - 1;
        int idx = n - 1;
        while (l <= r)
        {
            int sqL = nums[l] * nums[l];
            int sqR = nums[r] * nums[r];

            if (sqL > sqR)
            {
                ans[idx--] = sqL;
                l++;
            }
            else
            {
                ans[idx--] = sqR;
                r--;
            }
        }

        return ans;
    }
};