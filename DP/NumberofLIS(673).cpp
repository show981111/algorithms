class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 1;
        vector<int> memoLeng(nums.size(), 1);
        // the length of Longest subsequence ending with ith elem

        vector<int> memoNumber(nums.size());
        // the number of Longest subsequence ending with ith elem

        memoNumber[0] = 1;
        int maxLeng = 1;

        for (int i = 1; i < nums.size(); i++)
        {
            int curLength = 0;
            for (int k = 0; k < i; k++)
            {
                if (nums[k] < nums[i] && curLength < memoLeng[k] + 1)
                {
                    memoLeng[i] = memoLeng[k] + 1;
                    curLength = memoLeng[k] + 1;
                }
            } // set the length of Longest Subsequence

            if (memoLeng[i] == 1) // if the lenght is 1, automatically number is 1
                memoNumber[i] = 1;

            for (int k = 0; k < i; k++)
            {
                if (memoLeng[i] == memoLeng[k] + 1 && nums[k] < nums[i])
                {
                    memoNumber[i] += memoNumber[k];
                } // if it can make a incresing subsequence, add it to the number
            }

            if (maxLeng < memoLeng[i])
            {
                maxLeng = memoLeng[i];
            }
        }

        int count = 0;
        for (int i = 0; i < memoLeng.size(); i++)
        {
            if (memoLeng[i] == maxLeng)
            { // get the number of every max length(there could be multiple max length!)
                count += memoNumber[i];
            }
        }

        // for(auto i : memoLeng)
        //     cout << i << ' ';
        // cout << endl;
        // for(auto i : memoNumber)
        //     cout << i << ' ';
        // cout << endl;
        // cout << "----------------\n";

        return count;
    }
};