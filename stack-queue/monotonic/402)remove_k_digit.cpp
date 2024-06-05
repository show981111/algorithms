class Solution
{
public:
    /*
    One important observation: We need to remove the digit[i] IF digit[i] > digit[i+1]
    By removing bigger number on the left, we put smaller number to that position, reducing the number!
    Thus, we know it is the smallest number if digits are in increasing order!
    */
    string removeKdigits(string num, int k)
    {
        int targetSize = num.size() - k;
        if (targetSize == 0)
            return "0";
        int erased = 0;
        stack<int> leftIndices;
        leftIndices.push(0);
        for (int i = 1; i < num.size(); i++)
        {
            // we start erasing from the left since left is a higher position than right in terms of number size
            while (!leftIndices.empty() && num[leftIndices.top()] > num[i]) // Increasing stack!
            {
                num[leftIndices.top()] = '-';
                leftIndices.pop();
                erased++;
                if (erased == k)
                    break;
            }
            if (erased == k)
                break;
            leftIndices.push(i);
        }
        num.erase(remove(num.begin(), num.end(), '-'), num.end());
        while (erased < k)
        {
            num.pop_back();
            erased++;
        }
        int idx = 0;
        for (; idx < num.size(); idx++)
        {
            if (num[idx] != '0')
            {
                break;
            }
        }
        if (idx == num.size())
            return "0";

        return num.substr(idx);
    }
};

/**
 *
 * Using DP - MLE
 */

class Solution
{
public:
    /*
    Just erasing big digits in a greed manner won't work
    ex) 1432219, k = 3, -> 1219
        1221
    Problem is equiv to,
    Make the smallest number of length num.size() - k by picking digits in order.
    1434519
    _ _ _ _
    1 4 3 2
      3 2 2
      2 2 1
      2 1 9
    From each i_th position, using i ~ N digits, whats the min we can make?
    T(i, x) = using 0 ~ i digits, min number with x digits
    T(i+1,x) = min(T(i,x-1) CONCAT num[i], T(i,x))
    Basecase: T(0,x) = 0, T(y, 0) = 0
       0 1 2 3 x
    0. 0   X X X
    1. 0 c   X X
    2. 0       X
    i  0

    */

    string removeKdigits(string num, int k)
    {
        int targetSize = num.size() - k;
        if (targetSize == 0)
            return "0";
        char M = '9' + 5;

        vector<vector<string>> dp(num.size(), vector<string>(targetSize + 1, string(1, M)));
        for (int i = 0; i < num.size(); i++)
            dp[i][0] = "";
        dp[0][1] = string(1, num[0]);

        for (int i = 1; i < num.size(); i++)
        {
            for (int j = 1; j <= min(i + 1, targetSize); j++)
            {
                // can make at most i + 1 digits using 0 ~ i digits
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + num[i]);
                // both are the same size, so lexico order == numeric order
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }

        string &res = dp.back().back();
        int idx = 0;
        for (; idx < res.size(); idx++)
        {
            if (res[idx] != '0')
            {
                break;
            }
        }
        if (idx == res.size())
            return "0";
        // res.erase(remove(res.begin(), res.end(), '0'), res.end());

        return (dp.back().back().substr(idx));
    }
};