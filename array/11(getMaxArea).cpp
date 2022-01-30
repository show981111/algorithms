#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int maxArea = 0;
        int left = 0;
        int right = height.size() - 1;
        while (left < right)
        {
            int minHeight = height[left];
            bool isMinRight = false;
            if (height[left] > height[right])
            {
                minHeight = height[right];
                isMinRight = true;
            }
            int cur = minHeight * (right - left);
            if (maxArea < cur)
            {
                maxArea = cur;
            }
            if (isMinRight)
            {
                right--;
            }
            else
                left++;
        }
        return maxArea;
    }
};