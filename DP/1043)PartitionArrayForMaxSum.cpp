class Solution
{
public:
    /*
    Partition in subarray so cannot sort...
    Partition usually lead to backtracking => Memo dp
    A B C D E G H
    A B / C D / E G H
    A / B C D / E G H

    DECISION TREE
      1st.  2nd.  3rd group ...
      - 1   - 1
      - 2.  \ 2  - 1
      .     \ k  \ 2
      .           .
      .           .
      - k -1

    If it is tough to come up with Bottom up, just do top down.
    In the case of top down, make it to "return the answer" -> Easy to convert it to DP!
    Don't use pass by reference

    (2) Bottom up
    T(i) : MAx sum of Arr[:i]
    T(i) = MAX(T(i-1) + arr[i], T(i-2) + 2*max(arr[i:i+2]), ... , T(i-k) + k*max(arr[i:i+k]));
    Based on groups I can make for the last one, we just add the best sum.
    At index i, we have K choice. From a group of, 1, 2, ... k.
    Then, just use the best sum for the rest which we recoreded
    */
    int solve(vector<int> &arr, vector<int> &dp, int k, int curIndex)
    {
        if (curIndex >= arr.size())
        {
            return 0;
        }
        if (dp[curIndex] != -1)
        {
            return dp[curIndex];
        }
        int maxSum = 0;
        int curSum = 0;
        int groupRep = 0;
        for (int curGs = 1; curGs <= k; curGs++)
        {
            if (curIndex + curGs - 1 >= arr.size())
                break;

            groupRep = max(groupRep, arr[curIndex + curGs - 1]);
            curSum = groupRep * curGs;
            curSum += solve(arr, dp, k, curIndex + curGs);
            maxSum = max(maxSum, curSum);
        }
        return dp[curIndex] = maxSum;
    }

    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        vector<int> dp(arr.size(), -1);
        return solve(arr, dp, k, 0);
    }

    /**
     * BOTTOM UP
     */
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        vector<int> dp(arr.size(), 0); // max sum arr[:i]
        dp[0] = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            int groupRep = arr[i];

            for (int j = i; j >= max(0, i - k + 1); j--)
            {
                groupRep = max(groupRep, arr[j]);
                if (j == 0)
                    dp[i] = max(dp[i], groupRep * (i - j + 1));
                else
                    dp[i] = max(dp[i], dp[j - 1] + groupRep * (i - j + 1));
            }
        }
        return dp.back();
    }
};
