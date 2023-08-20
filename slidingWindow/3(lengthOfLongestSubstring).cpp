// substring question... dp or sliding window...
// total number of ascii code, 128.
/**
 * @brief Sliding Window
 * Brute force: counting from every index. ex) starting from 0, count, from 1, count ...
 * Can we make O(N) using catapillar?
 *
 * After we forward right, do we need to go back? No! it will anyways smaller than current maxLeng if we go back
 * So, we can just keep forwarding right and left.
 * Since left go through string once, right go through string once, total O(2N) => O(N)!!!
 *
 */
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int loc[128];
        fill(loc, loc + 128, -1);
        size_t maxLeng = 0;
        size_t left = 0, right = 0;
        size_t N = s.size();

        while (left < N && right < N)
        { // if we remove right, then it will go out of bound.
            // We can escape when right goes above the bound because we know that
            //  longest lenght will come with smallest left and largest right, which comes first.
            unsigned int num = s[right];
            if (loc[num] == -1)
            {
                loc[num] = right;
                right++;
                maxLeng = max(maxLeng, right - left); // we can put this here not at the end of
                // while loop because we only update the length when we forward the right!
            }
            else
            {
                int clearUntil = loc[num];
                for (; left <= clearUntil; left++)
                {
                    if (left >= N)
                        break;
                    loc[(unsigned int)s[left]] = -1;
                }
            }
        }

        return maxLeng;
    }
};

/**
 * Previous version
 */

#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    void resetArray(int *arr, int x)
    {
        for (int i = 0; i < 130; i++)
        {
            arr[i] = x;
        }
    }
    int lengthOfLongestSubstring(string s)
    {
        int position[130];
        resetArray(position, -1);
        int total = 0;
        int cur = 0;
        for (int i = 0; i < s.length(); i++)
        {
            size_t index = s[i];
            if (position[index] == -1)
            {
                position[index] = i;
                cur++;
            }
            else
            {
                cur = 0;
                i = position[index];
                resetArray(position, -1);
            }
            if (total < cur)
                total = cur;
        }
        return total;
    }
};