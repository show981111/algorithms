/*
    Intuition for Two Pointers.
    How do we know if a string is palindrome or not?
    -> use two pointers from the beginning and the end.
    OR from the middle, go to the beginning and the end => O(N)
    Since DP is O(N^2), can we just use this method per each character?
    YES!
*/

/**
 * @brief For each mid, we push left and right to the farthest!
 * We first go to the point where mid != left, mid != right
 * to consider like ca[a]aaaad. if we have a subsequent redundant letters,
 * it can form palindrome regardless of mid's position if we adjust mid properly.
 *
 * Then, we push left and right to the farthest!!
 *
 * @brief We can solve this using a DP
 * T(i, j) = T(i+1, j-1) && s[i] == s[j]
 * s[i:j] is a palindrome if s[i+1:j-1] is a palindrome and s[i] == s[j]!
 * => Thus, we should traverse the memo a lil differently. \\\ this direction
 * for(offset = 0 ~ end){
 *      for(row = 0 ~ end - offset){
 *          col = row + offset
 *      }
 * }
 * -> (0,0) -> (1,1) -> (2,2) ... / -> (0,1) -> (1,2) -> ...
 * So, we have a 2D memo
 *
 * Time complexity is pretty much same,
 * both O(N^2)
 *
 */
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int N = s.size();
        int maxStart = 0;
        int maxLeng = 0;
        for (int mid = 0; mid < N; mid++)
        {
            if (mid > 0 && s[mid] == s[mid - 1]) // no need to calculate cuase we count
                continue;                        // the redundant mid before

            int left = mid, right = mid;
            while (left >= 0 && s[mid] == s[left])
                left--;
            while (right < N && s[mid] == s[right]) // push further until it pass the redundant mid
                right++;
            while (left >= 0 && right < N && s[left] == s[right]) // push further until it is a palindrome
            {
                left--;
                right++;
            } // left +1 ~ right -1 is palindrome

            if (right - left - 1 > maxLeng)
            {
                maxLeng = right - left - 1;
                maxStart = left + 1;
            }
        }
        return s.substr(maxStart, maxLeng);
    }
};

/**
 * @brief Using DP
 *
 */

// palindrome -> famous DP problem
/* T(N,M) = T(N+1, M-1) && a[N] == a[M]
   [] b a b a d
[] T. F F F F F
b. F. T F T
a  F. X T F
b. F. X X T
a  F. X X X T
d. F  X X X X T

The direction of iteration is important. Since u need (N+1, M-1) entry,
I need to traverse from down to up so that (N+1, M-1) entry is calculated before (N,M)
(0,0) -> (1,1) -> (1,0) -> (2,2) -> (2,1) -> (2,0) ...
         [for each col, row is going up!]
*/
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int N = s.size();
        vector<vector<bool>> memo(N + 1, vector<bool>(N + 1, false));
        memo[0][0] = true;
        int maxLeng = 0;
        int maxStart = 0;

        for (int col = 1; col < N + 1; col++)
        {
            for (int row = col; row >= 1; row--)
            {
                if (row + 1 <= col - 1)
                {
                    memo[row][col] = memo[row + 1][col - 1] && (s[row - 1] == s[col - 1]);
                }
                else
                {
                    memo[row][col] = s[row - 1] == s[col - 1];
                }
                if (memo[row][col] && col - row + 1 > maxLeng)
                {
                    maxLeng = col - row + 1;
                    maxStart = row - 1;
                }
            }
        }
        return s.substr(maxStart, maxLeng);
    }
};