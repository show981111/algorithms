class Solution
{
public:
    bool isPalindrome(string s)
    {
        int left = 0;
        int right = s.size() - 1;

        while (left < right)
        {
            while (left < s.size() && !isalnum(s[left]))
                left++;
            while (right >= 0 && !isalnum(s[right]))
                right--;
            if (left >= right || left >= s.size() || right < 0)
                break;
            // we can just do this without if condition
            // we increase left until right, which means it could be left == right
            // after the first iternation
            // if its all non-alphanumeric, left == right after 1st iter
            // while(left < right && !isalnum(s[left]))
            //     left++;
            // while(left < right && !isalnum(s[right]))
            //     right--;

            if (tolower(s[left]) == tolower(s[right]))
            {
                left++;
                right--;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};