/**
 * @brief Using a Two Pointer
 * The idea here is for each "mid"(each index of string we set the index as a mid point),
 * we enlarge the left and right so that we can find the longest palindrome
 *
 */

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int start = 0, leng = 0;
        int N = s.length();
        for (int mid = 0; mid < N; mid++)
        {
            int right = mid;
            while (right < N && s[mid] == s[right])
                right++; // push right to the same letters
            // Now s[mid~right-1] are all same letters ex) "aaaa"

            // why we are doing this? : bb is palindrome but ab is not
            // since the same letters are always palindrome, we should push the range to
            // farthest to set the starting point.
            // Suppose right = mid, left = mid - 1
            // ex) babad : if we compare right and left from the start, then it cannot find
            // any palindrome because all adjacent letters are different
            // suppose right = mid - 1, left = mid + 1
            // ex) cbbd : in this case "bb" is a palindrome but comparing right and left
            // cannot notice this because right and left are not adjacent

            int left = mid - 1;
            while (left >= 0 && right < N && s[left] == s[right])
            {
                left--;
                right++;
            }
            // Now s[left+1 ~ right-1] is a palindrome

            if (right - left - 1 > leng)
            {
                leng = right - left - 1;
                start = left + 1;
            }
        }
        return s.substr(start, leng);
    }
};