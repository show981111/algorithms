/*
** TWO POINTERS + GREEDY **
Brute force-> for all pair, get area => O(N^2)
Area = x distance * min height
Starting from leftmost & rightmost to maximize x_distance.
The only way to increase the area is?
increase the height.. cause x_distance will decrease.
How to increase the height? -> move the shorter one!
Since shorter one decide the height!
Don't care about it will decrease or increase the height.
 *** Only way we can "possibly" increase *** the height is moving shorter one.
Edge case)
5 1 100 100 1 10.. ? -> Still moving shorter one works!

Key point of using two pointers to make something LINEAR,
Find a condition that will not give us a possible answer.
FOr example, if we go left, we won't get what we want (0% to get what we want)
Go right, we might! get what we want (X% > 0).
What we have to do is find that condition that can exclude one path!
*/
class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int left = 0, right = height.size() - 1;
        int maxArea = 0;
        while (left < right)
        {
            int curArea = (right - left) * min(height[left], height[right]);
            maxArea = max(curArea, maxArea);
            if (height[left] > height[right])
                right--;
            else
                left++;
        }

        return maxArea;
    }
};
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