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