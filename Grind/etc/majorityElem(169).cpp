class Solution
{
public:
    /**
     * To conclude, space complexity of recursive algorithm is proportinal to
     * maximum depth of recursion tree generated. If each function call of recursive
     * algorithm takes O(m) space and if the maximum depth of recursion tree is 'n'
     *  then space complexity of recursive algorithm would be O(nm).
     */
    // Time complexity : O(nlogn) bc) T(n) = 2T(n/2)[two recursive getMaj] + O(n)[counting lmCounter, rmCounter]
    // Space complexity : O(logn) => Recursive stack, the height of tree is logN!
    int getMajority(vector<int> &nums, int start, int end)
    {
        if (start == end)
            return nums[start];

        int mid = start + (end - start) / 2;
        int leftMajor = getMajority(nums, start, mid);
        int rightMajor = getMajority(nums, mid + 1, end);

        if (leftMajor == rightMajor)
            return leftMajor;
        else
        {
            int lmCounter = count(nums.begin() + start, nums.begin() + end + 1, leftMajor);
            int rmCounter = count(nums.begin() + start, nums.begin() + end + 1, rightMajor);
            return lmCounter > rmCounter ? leftMajor : rightMajor;
        }
    }
    int majorityElement(vector<int> &nums)
    {
        // 1. using sort: Time: O(nlogn), Space: O(1)
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];

        // 2. Moore's algorithm: Time: O(n), space : O(1)
        int count = 0, maj = 0;
        for (auto num : nums)
        {
            if (count == 0)
            { // if count == 0, update majority
                maj = num;
                count++;
            }
            else
            {
                if (num == maj)
                    count++; // accumulate counter
                else
                    count--; // if it is not a maj, then cancel the counter
            }
        }
        return maj; // final survivor should be a maj since counter for maj is > n/2

        // 3. Divide and Conquer
        return getMajority(nums, 0, nums.size() - 1);
    }
};