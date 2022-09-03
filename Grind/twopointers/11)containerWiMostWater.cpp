/**
 * @brief Two pointers and Greedy.
 *
 * We should think how we can maximize the area of container
 * At I_th step, what should we do? How should we shrink the two poniters?
 * The way we can increase the area of container is by increasing a height(since
 * right - left is fixed)
 *
 * 1) should we compare height[left] vs height[left+1] ?
 * NO! this will make two pinters not shrink if height[left] > height[left+1]
 * We should! shrink the pointers but important thing is how.
 *
 * ## SO, we should shrink in a way to maximize the probability of getting big area.
 * if we shrink the side that is shorter, than area will just decrease.
 * Why? the height will be less then current height, or at most current height.
 * Thus, the area should be decreased.
 *
 * Therefore, only chance we have is by shrinking the side which has a shorter height.
 *
 */

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int left = 0, right = height.size() - 1;
        int area = 0;
        while (left < right)
        {
            area = max(area, min(height[left], height[right]) * (right - left));
            if (height[left] > height[right])
                right--;
            else
                left++;
        }
        return area;
    }
};