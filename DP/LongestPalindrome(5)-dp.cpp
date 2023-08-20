/**
 * @brief Our memo is 2D memo with start - end
 * EX) babad
 *   b a b a d
 * b T F T
 * a X T F T
 * b X X T F
 * a X X X T F
 * d X X X X T
 *
 * Row is start letter and column is the end letter
 * T(start, end) = T(start + 1, end - 1) && s[start] == s[end]
 *               # the letter between start and end should be a palindrome
 *               # and also, the start and end letter should be equal to be a palindrome
 *
 * Since we are using a 2D memo, using a bottm-up we can save the space by using a 1D memo.
 *
 */

class Solution
{
public:
    string longestPalindrome(string s)
    { // abbcdcbfg
        vector<vector<bool>> memo(s.size(), vector<bool>(s.size(), true));
        int N = s.size();

        int maxStart = 0, maxLeng = 0;
        for (int j = 1; j < N; j++)
        {
            for (int i = 0; i < N - j; i++)
            {
                int row = i;       // start
                int col = row + j; // end
                // T(s,e) = arr[s] == arr[e] && T(s+1,e-1);
                memo[row][col] = ((s[row] == s[col]) && memo[row + 1][col - 1]);
                if (memo[row][col] && col - row > maxLeng)
                {
                    maxLeng = col - row;
                    maxStart = row;
                }
            }
        }
        // cout << maxLeng << endl;
        return s.substr(maxStart, maxLeng + 1);
    }
};