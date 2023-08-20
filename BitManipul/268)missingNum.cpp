/**
 * @brief Bit manipul
 *
 */

class Solution
{
public:
    int missingNumber(vector<int> &nums)
    {
        int n = nums.size();
        int num = 0;
        // X^X = 0;
        // X^0 = X;
        // 1^2^3^4^(1^2^3^4^5)
        for (int i = 0; i < n; i++)
        {
            num = num ^ i;
            num = num ^ nums[i];
        }
        num = num ^ n;
        return num;
    }
};

/**
 * @brief Since number range is 0 ~ N, we can use this info
 * to mark its presence!
 *
 */

class Solution
{
public:
    int missingNumber(vector<int> &nums)
    {
        int n = nums.size();
        bool isNHere = false;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == n || nums[i] == 2 * n + 1)
                isNHere = true;
            else
            {
                int idx = nums[i];
                if (nums[i] >= n + 1) // For 0, we cannot do -0, so use n + 1 as an offset!
                {
                    idx = idx - n - 1;
                }
                nums[idx] = n + 1 + nums[idx];
            }
        }
        if (!isNHere)
            return n;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < n + 1)
            {
                return i;
            }
        }
        return -1;
    }
};