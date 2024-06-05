class Solution
{
public:
    /*
    Bforce: O(N^2)

    How to compute sum of differences with other numbes, without iterating all other numbers at each number?

    => Delta sum technique. (`/algorithms/Tree/cses_tree_distance2.cpp`)
    As we move, we can think of it as getting close to the rest of elements in the line, but farther away from the
    elements behind us!!

     d1.  d2 d3. d4.
    a - b - c - d - e
    result[a] = d1 + (d1+d2) + (d1+d2+d3) + (d1+d2+d3+d4)
    result[b] = d1 + d2 + (d2+d3) + (d2+d3+d4) = result[a] -4*d1 +d1(get close to b,c,d,e, farther away from a)
    result[c] = (d1+d2) + d2 + d3 + (d3+d4) = result[b] -3*d2 + 2*d2 (get close to c,d,e but farther away from a,b)
    result[d] =
    result[e] =
    */
    vector<int> getSumAbsoluteDifferences(vector<int> &nums)
    {
        vector<int> ans(nums.size());
        for (int i = 0; i < nums.size() - 1; i++)
        {
            int d = nums[i + 1] - nums[i];
            ans[0] += d * (nums.size() - (i + 1));
        }
        for (int i = 1; i < nums.size(); i++)
        {
            // From previous sum, close to the rest of numbers, but farther away from previous numbers.
            int d = nums[i] - nums[i - 1];
            ans[i] = ans[i - 1] - (nums.size() - i) * d + i * d;
        }
        return ans;
    }
};