/**
 * @brief Palindrome DP + minimum number of cuts DP
 * IsPalindrome(row, col) = IsPalindrome(row+1, col-1) && s[row] == s[col]
 * MinCuts(i) = min(MinCuts[k-1] + 1), where s[k:i] is palindrome
 * (min # of cuts of s[:i])
 *
 * TC: O(N^2), SC: O(N^2)
 *
 * Anohter solution would be using a bactrack with memo
 */
class Solution
{
public:
    int minCut(string s)
    {
        int N = s.size();
        vector<vector<bool>> memo(N + 1, vector<bool>(N + 1, true));
        vector<int> count(N, 0);
        for (int i = 0; i < N; i++)
        {
            count[i] = i;
        }

        for (int k = 1; k < N; k++)
        {
            for (int row = 1; row < N + 1 - k; row++)
            {
                int col = row + k;
                memo[row][col] = memo[row + 1][col - 1] && s[row - 1] == s[col - 1];
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int from = 0; from <= i; from++)
            {
                if (memo[from + 1][i + 1])
                {
                    if (from == 0)
                        count[i] = min(count[i], count[from]);
                    else
                        count[i] = min(count[i], count[from - 1] + 1);
                }
            }
        }

        return count.back();
    }
};

/**
 * @brief Traversing differnt direction
 *
 */

class Solution
{
public:
    int minCut(string s)
    {
        int N = s.size();
        vector<vector<bool>> memo(N + 1, vector<bool>(N + 1, true));
        vector<int> count(N + 1, 0);
        for (int i = 0; i < N + 1; i++)
        {
            count[i] = i - 1; // 1 indexed. count is minCuts for s[:i] = count[i+1]
        }

        // palindrome different traverse direction.
        //  for each column, bottom row to top row
        for (int col = 2; col < N + 1; col++)
        {
            for (int row = col - 1; row >= 1; row--)
            {
                memo[row][col] = memo[row + 1][col - 1] && s[row - 1] == s[col - 1];
                if (memo[row][col])
                {
                    count[col] = min(count[col], count[row - 1] + 1);
                }
            }
            count[col] = min(count[col], count[col - 1] + 1);
        }

        return count.back();
    }
};

/**
 * @brief Backtrack with memo
 *
 */

class Solution
{
public:
    // vector<vector<int>> memo;
    vector<vector<int>> helperMemo;
    bool isPalindrome(string &s, int start, int end)
    {
        int mid = (start + end) / 2;
        for (int i = start; i <= mid; i++)
        {
            if (s[i] != s[end - i + start])
                return false;
        }
        return true;
    }
    int helper(string &s, int start, int end)
    {
        if (start >= end)
            return 0;
        if (helperMemo[start][end] != -1)
            return helperMemo[start][end];
        if (isPalindrome(s, start, end))
        {
            helperMemo[start][end] = 0;
            return 0;
        }
        int minCut = end - start + 1;
        for (int i = start; i < end; i++)
        {
            // Optimization here is we only considers when start ~ i is a
            // palindrome!
            // guranteed to get a minimum because we consider this for all indices
            if (isPalindrome(s, start, i))
            {
                int cand = helper(s, i + 1, end) + 1;
                minCut = min(minCut, cand);
            }
        }
        helperMemo[start][end] = minCut;
        return minCut;
    }
    int minCut(string s)
    {
        helperMemo.resize(s.size(), vector<int>(s.size(), -1));
        return helper(s, 0, s.size() - 1);
    }
};