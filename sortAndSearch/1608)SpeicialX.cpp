class Solution
{
public:
    /*
    Find x such that, exactly x numbers in the array >= x.
    0 <= x <= |array|
    Gussing the x in the range.. maybe Bin search?
    Then, how can we cut off the search range?
    */
    int findX(vector<int> &nums, int start, int end)
    {
        if (start > end)
            return -1;

        int mid = (start + end) / 2;
        int sz = nums.end() - lower_bound(nums.begin(), nums.end(), mid);
        if (sz == mid)
            return mid;
        if (sz > mid)
        {
            // lots of numbers are greater than mid, so # Greater than X_1 > X_1
            // If we choose smaller X, than it will have more numbers that are greater than X.
            // EX) X_2 < X_1, so # Greater than X_2 > # Greater than X_1 > X_1 Thus, X_2 cannot be a candidate
            return findX(nums, mid + 1, end);
        }
        else
        {
            // few numbers are greater than mid, so we should choose smaller one.
            // Suppose we choose X_2 > X_1, since few numbers are greater than mid, # Greater than X_1 < X_1
            // # Greater than X_2 < # Greater than X_1 < X_1, so # Greater than X_2 < X_1
            return findX(nums, start, mid - 1);
        }
    }
    int specialArray(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        return findX(nums, 0, nums.size());
    }
};
