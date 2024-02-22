class Solution
{
public:
    /*
     if you have k (k >= 3) positive real numbers a1, a2, a3, ..., ak where
     (*) a1 <= a2 <= a3 <= ... <= ak
     (*) and a1 + a2 + a3 + ... + ak-1 > ak,
     then there always exists a polygon with k sides whose lengths are a1, a2, a3, ..., ak.

     Use those two conditions.

     1 1 2 3 5 12 50
     If x1 x2 x3 x4 < x5,
     x1 x2 x3 x4 x5 < x6? Nope but, as long as
     x1 x2 x3 x4 x5 > x6, perimeter is just sum of everything
     There is no benefit in shrinking the window ex) x2 + ,,, + x_n since lhs should big!
     This leads to greedy solution
    */
    long long largestPerimeter(vector<int> &nums)
    {
        long long largestPerimeter = -1;
        long long s = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (i >= 2)
            {
                if (s > nums[i])
                {
                    largestPerimeter = max(largestPerimeter, s + nums[i]);
                }
            }
            s += nums[i];
        }
        return largestPerimeter;
    }
};