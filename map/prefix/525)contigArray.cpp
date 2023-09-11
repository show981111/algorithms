/*
Initial thought
// 0 0 0 0 1 1
// 1 2 3 4 4 4 (#zeros)
// 0 0 0 0 1 2 (#ones)
// Find the point where, Cur 1's - 1's to i == Cur 0's - 0's to i => Length = J - i
However, the problem is, we need to anyways go back, and iterate from starting point to end point
Which will be O(N^2). Also, we don't know where to start because the number of ones or number of zeros
we need can change because when we go back, #1's and #0's can both change!

What we should do? How should we know where to start..?

The key is, it is binary! only 0's and 1's. This means, if 0 -> (-1), then the question is the same as
finding the max length that the sum of subarray is zero!
Now question is, when curSum != 0, how do we know where to look?
Just like target sum count, we store the prefix in Map.
But, is the prefix sum unique for each position? NO! Then, which one we should follow?
Keep the smallest one! because we need to get a max length, and all we need is the prefix sum is
what we are looking for.

// sum[0:j] - sum[0:i] = sum[i+1 : j] = target
// sum[0:j] - target = sum[0:i] -> we are looking for this i.
*/

class Solution
{
public:
    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> sumPath;
        int curSum = 0;
        int maxLength = 0;
        sumPath[0] = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
                curSum--;
            else
                curSum++;
            if (sumPath.find(curSum) != sumPath.end())
            {
                maxLength = max(maxLength, i - sumPath[curSum]);
            }
            else
            {
                sumPath[curSum] = i;
            }
            sumPath[curSum] = min(i, sumPath[curSum]);
        }

        return maxLength;
    }
};