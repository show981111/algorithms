/**
 * @brief More simple and felxible sliding window
 * It is more like a two pointer!
 * We have left and right. we can shrink the window and enlarge the window
 * depending on situation!
 *
 */

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        bool arr[100] = {
            false,
        };
        int N = s.length();
        int left = 0, right = 0;
        int maxLength = 0;
        while (left < N && right < N)
        {
            int index = s[right] - ' ';

            if (arr[index] == false)
            {
                arr[index] = true;
                right++;
            }
            else
            {
                maxLength = max(maxLength, right - left);
                arr[s[left++] - ' '] = false; // hit the wall, so shrink left
            }
        }
        maxLength = max(maxLength, right - left);
        return maxLength;
    }
};

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int arr[100] = {
            -1,
        };
        for (int i = 0; i < 100; i++)
            arr[i] = -1;
        int N = s.length();
        int maxLength = 0;
        int start = 0;
        int i = 0;
        for (; i < N;)
        {
            int index = s[i] - ' ';
            if (arr[index] == -1)
            {
                arr[index] = i;
                i++;
            }
            else
            {
                maxLength = max(maxLength, i - start);
                int nextStart = arr[index] + 1;
                for (int k = start; k <= i; k++)
                    arr[s[k] - ' '] = -1;

                start = nextStart;
                i = start;
            }
        }
        maxLength = max(maxLength, i - start); // if the last letter is not redundant,
        // then i is equal to length of string!
        return maxLength;
    }
};