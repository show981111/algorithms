class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        /*
                1 3 4 5  2  3
        running 1 4 8 13 15 18
        subarr sum[i:j] = running total to j - running total to i -1  = k?
        we need (running total to j) - (k) to be equal to (running total to i - 1)
        */
        int c = 0;
        unordered_map<int, int> weHave;
        weHave[0] = 1;
        int runningSum = 0;
        for (int num : nums)
        {
            runningSum += num;
            auto target = weHave.find(runningSum - k);
            if (target != weHave.end())
            {
                c += target->second;
            }
            weHave[runningSum]++;
        }
        return c;
    }
};