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
        int mid = 0;
        int left = mid, right = mid;
        int ans = 0;
        int maxLeft = 0;
        while (mid < s.size() - ans / 2)
        {
            // mid < s.size() - ans
            // if we do this, then we will miss the possible solution because
            // for each mid, the max length could be (end - mid) * 2
            while (left >= 0 && s[mid] == s[left])
                left--;
            while (right < s.size() && s[right] == s[mid])
                right++;
            while (left >= 0 && right < s.size() && s[left] == s[right])
            {
                left--;
                right++;
            }
            // cout << left << " " << right << endl;
            if (ans < right - left - 1)
            {
                maxLeft = left + 1;
                ans = right - left - 1;
            }

            mid++;
            left = mid;
            right = mid;
        }
        return s.substr(maxLeft, ans);
    }
};