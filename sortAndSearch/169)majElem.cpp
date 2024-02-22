class Solution
{
public:
    /*
    Divide & Conquer: if x is the major, x should be a major of left half or right half
    Total N elem. if x is not a major if left and right.
    L_maj > n/4
    R_maj > n/4
    So, L_maj + R_maj > n/2, Thus, x cannot be a major
    */
    int getMaj(vector<int> &nums, int start, int end)
    {
        if (start == end)
            return nums[start];
        int mid = start + (end - start) / 2;
        int Lmaj = getMaj(nums, start, mid);
        int Rmaj = getMaj(nums, mid + 1, end);

        // Merge -> We should search start ~ end.. not start - mid , mid - end why?
        // 1 1 0 2 / 2 2 1 1 : LM = 1, RM = 2 (if we break tie by LM)
        // then RM will win at the end. We need to evaluate from merged Array!
        int Lcount = count(nums.begin() + start, nums.begin() + end + 1, Lmaj);
        int Rcount = count(nums.begin() + start, nums.begin() + end + 1, Rmaj);

        if (Lcount >= Rcount)
            return Lmaj;
        else
            return Rmaj;
    }

    int majorityElement(vector<int> &nums)
    {
        return getMaj(nums, 0, nums.size() - 1);
    }
};
