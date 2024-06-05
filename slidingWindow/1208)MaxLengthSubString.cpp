class Solution
{
    /**
     * Maximization + Substring? -> Sliding Window or DP
     *
     * We are interested in sum of the cost of the substring.
     * Do we need to consider all substrings? (O(N^2))
     * We only want to know the big ones.
     * Starting at I, if I ~ J goes above the cost, we don't have to consider any substrings within I ~ J since they will be
     * anyways smaller than I ~ J. Thus, we can just move to next possible I and stretch J to the right.
     * This is the case even tho some cost is negative!
     */
public:
    int equalSubstring(string s, string t, int maxCost)
    {
        int i = 0, j = 0;
        int curCost = 0;
        int leng = 0;
        while (j < s.size())
        {
            // consider substring starting at I
            while (j < s.size() && curCost <= maxCost)
            {
                curCost += abs(s[j] - t[j]);
                leng = max(leng, j - i);
                j++;
            } // stretch. Once stretch, do we need to go back? Nope. going back only reduces the length of substring
            // Since substring I ~ J is longer than I+k ~ J, we can skip if cost goes over.
            while (i < j && curCost > maxCost)
            {
                curCost -= abs(s[i] - t[i]);
                i++;
            } // shrink. Do we need to go back? Nope. previous starting point is already considered before.
            leng = max(leng, j - i);
        }

        return leng;
    }
};
